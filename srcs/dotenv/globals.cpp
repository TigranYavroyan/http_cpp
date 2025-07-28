#include <globals.h>

namespace Karich {
	#ifdef PROJECT_ROOT
		const std::string globals::project_root = PROJECT_ROOT;
		const std::string& globals::get_project_root () {
			return project_root;
		}
	#else
		#error "Define project root folder"
	#endif

}