#ifndef GLOB_HPP
#define GLOB_HPP

#include <string>

namespace Karich {
	
	class globals {
#ifdef PROJECT_ROOT
	private:
		const static std::string project_root;
	public:
		static const std::string& get_project_root ();
#else
	#error "Define the project root"
#endif
};
}

#endif // GLOB_HPP