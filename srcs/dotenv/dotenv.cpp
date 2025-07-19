#include <dotenv.h>
///
/// Read and initialize environment variables from the `.env` file, or a file
/// specified by the \a filename argument.
///
/// \param filename a file to read environment variables from
///
void dotenv::init(const char* filename)
{
    dotenv::do_init(OptionsNone, filename);
}

///
/// Read and initialize environment variables using the provided configuration
/// flags.
///
/// By default, if a name is already present in the environment, `dotenv::init()`
/// will replace it with the new value. To preserve existing variables, you
/// must pass the `Preserve` flag.
///
/// \code
/// dotenv::init(dotenv::Preserve);
/// \endcode
///
/// \param flags    configuration flags
/// \param filename a file to read environment variables from
///
void dotenv::init(int flags, const char* filename)
{
    dotenv::do_init(flags, filename);
}

///
/// Wrapper for std::getenv() which also takes a default value, in case the
/// variable turns out to be empty.
///
/// \param name the name of the variable to look up
/// \param def  a default value
///
/// \returns the value of the environment variable \a name, or \a def if the
///          variable is not set
///
std::string dotenv::getenv(const char* name, const std::string& def)
{
    const char* str = std::getenv(name);
    return str ? std::string(str) : def;
}

#if defined(_MSC_VER) || defined(__MINGW32__)

// https://stackoverflow.com/questions/17258029/c-setenv-undefined-identifier-in-visual-studio
int setenv(const char *name, const char *value, int overwrite)
{
    int errcode = 0;

    if (!overwrite)
    {
        size_t envsize = 0;
        errcode = getenv_s(&envsize, NULL, 0, name);
        if (errcode || envsize) return errcode;
    }
    return _putenv_s(name, value);
}

#endif // _MSC_VER

///
/// Look for start of variable expression in input string
/// on the form $VARIABLE or ${VARIABLE}
///
/// \param str  in:  string to search in
/// \param pos  in:  search from position
/// \param pos  out: start tag found
///
/// \returns The start position of next variable expression or std::string::npos if not found
///
size_t dotenv::find_var_start(const std::string& str, size_t pos, std::string& start_tag)
{
   size_t p1      = str.find('$',pos);
   size_t p2      = str.find("${",pos);
   size_t pos_var = (std::min)(p1,p2);
   if(pos_var != std::string::npos) start_tag = (pos_var == p2)? "${":"$";
   return pos_var;
}

///
/// Look for end of variable expression in input string
/// on the form $VARIABLE or ${VARIABLE}
///
/// \param str  in:  string to search in
/// \param pos  in:  search from position (result from find_var_start)
/// \param pos  in:  start tag
///
/// \returns The next end position of variable expression or std::string::npos if not found
///
size_t dotenv::find_var_end(const std::string& str, size_t pos, const std::string& start_tag)
{
   char end_tag    = (start_tag == "${")? '}':' ';
   size_t pos_end  = str.find(end_tag,pos);
   // special case when $VARIABLE is at end of str with no trailing whitespace
   if(pos_end == std::string::npos && end_tag==' ') pos_end = str.length();
   return pos_end;
}

// trim whitespace from left (in place)
void dotenv::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c); }));
}

// trim whitespace from right (in place)
void dotenv::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {return !std::isspace(c); }).base(), s.end());
}

// trim both ends (in place)
void dotenv::trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

// trim from both ends (copying)
std::string dotenv::trim_copy(std::string s) {
    trim(s);
    return s;
}

///
/// Resolve variables of the form $VARIABLE or ${VARIABLE} in a string
///
/// \param iline line number in .env file
/// \param str   the string to be resolved, containing 0 or more variables
/// \param ok    true on return if no variables found or all variables resolved ok
///
/// \returns pair with <resolved, true> if ok, or <partial, false> if error
///
std::pair<std::string, bool> dotenv::resolve_vars(size_t iline, const std::string& str)
{
   std::string resolved;

   size_t pos = 0;
   size_t pre_pos = pos;
   size_t nvar = 0;

   bool finished=false;
   while(!finished)
   {
      // look for start of variable expression after pos
      std::string start_tag;
      pos = find_var_start(str,pos,start_tag);
      if(pos != std::string::npos)
      {
         // a variable definition detected
         nvar++;

         // keep start of variable expression
         size_t pos_start = pos;

         size_t lstart = start_tag.length();  // length of start tag
         size_t lend   = (lstart>1)? 1 : 0;   // length of end tag

         // add substring since last variable
         resolved += str.substr(pre_pos,pos-pre_pos);

         // look for end of variable expression
         pos = find_var_end(str,pos,start_tag);
         if(pos != std::string::npos)
         {
            // variable name with decoration
            std::string var = str.substr(pos_start,pos-pos_start+1);

            // variable name without decoration
            std::string env_var = var.substr(lstart,var.length()-lstart-lend);

            // remove possible whitespace at the end
            rtrim(env_var);

            // evaluate environment variable
            if(const char* env_str = std::getenv(env_var.c_str()))
            {
               resolved += env_str;
               nvar--; // decrement to indicate variable resolved
            }
            else
            {
               // could not resolve the variable, so don't decrement
               std::cout << "dotenv: Variable " << var << " is not defined on line " << iline << std::endl;
            }

            // skip end tag
            pre_pos = pos+lend;
         }
      }
      else {
         // no more variables
         finished = true;
      }
   }

   // add possible trailing non-whitespace after last variable
   if(pre_pos < str.length())
   {
      resolved += str.substr(pre_pos);
   }

   // nvar must be 0, or else we have an error
   return std::make_pair(resolved,(nvar==0));
}

void dotenv::do_init(int flags, const char* filename)
{
    std::ifstream file;
    std::string line;

    file.open(filename);

    if (file)
    {
        unsigned int i = 1;

        while (getline(file, line))
        {
            const auto len = line.length();
            if (len == 0 || line[0] == '#') {
                continue;
            }

            const auto pos = line.find("=");

            if (pos == std::string::npos) {
                std::cout << "dotenv: Ignoring ill-formed assignment on line "
                          << i << ": '" << line << "'" << std::endl;
            } else {
                auto name = trim_copy(line.substr(0, pos));
                auto line_stripped = strip_quotes(trim_copy(line.substr(pos + 1)));

                // resolve any contained variable expressions in 'line_stripped'
                auto p = resolve_vars(i,line_stripped);
                bool ok = p.second;
                if(!ok) {
                   std::cout << "dotenv: Ignoring ill-formed assignment on line "
                   << i << ": '" << line << "'" << std::endl;
                }
                else {

                   // variable resolved ok, set as environment variable
                   const auto& val = p.first;
                   setenv(name.c_str(), val.c_str(), ~flags & dotenv::Preserve);
                }
            }
            ++i;
        }
    }
    else {
        throw std::invalid_argument(std::strerror(errno));
    }
}

std::string dotenv::strip_quotes(const std::string& str)
{
    const std::size_t len = str.length();

    if (len < 2)
        return str;

    const char first = str[0];
    const char last = str[len - 1];

    if (first == last && ('"' == first || '\'' == first))
        return str.substr(1, len - 2);

    return str;
}