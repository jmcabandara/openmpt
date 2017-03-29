 
 project "libopenmpt"
  uuid "9C5101EF-3E20-4558-809B-277FDD50E878"
  language "C++"
  location ( "../../build/" .. mpt_projectpathname )
  vpaths { ["*"] = "../../" }
  mpt_projectname = "libopenmpt"
  dofile "../../build/genie/genie-defaults-LIBorDLL.lua"
  dofile "../../build/genie/genie-defaults.lua"
  dofile "../../build/genie/genie-defaults-winver.lua"
  local extincludedirs = {
   "../../include",
   "../../include/ogg/include",
   "../../include/vorbis/include",
   "../../include/zlib",
  }
  includedirs ( extincludedirs )
  includedirs {
   "../..",
   "../../common",
   "../../soundlib",
   "$(IntDir)/svn_version",
   "../../build/svn_version",
  }
  files {
   "../../common/*.cpp",
   "../../common/*.h",
   "../../soundbase/*.cpp",
   "../../soundbase/*.h",
   "../../soundlib/*.cpp",
   "../../soundlib/*.h",
   "../../soundlib/plugins/*.cpp",
   "../../soundlib/plugins/*.h",
   "../../soundlib/plugins/dmo/*.cpp",
   "../../soundlib/plugins/dmo/*.h",
   "../../libopenmpt/libopenmpt.h",
   "../../libopenmpt/libopenmpt.hpp",
   "../../libopenmpt/libopenmpt_config.h",
   "../../libopenmpt/libopenmpt_ext.hpp",
   "../../libopenmpt/libopenmpt_impl.hpp",
   "../../libopenmpt/libopenmpt_internal.h",
   "../../libopenmpt/libopenmpt_stream_callbacks_buffer.h",
   "../../libopenmpt/libopenmpt_stream_callbacks_fd.h",
   "../../libopenmpt/libopenmpt_stream_callbacks_file.h",
   "../../libopenmpt/libopenmpt_version.h",
   "../../libopenmpt/libopenmpt_c.cpp",
   "../../libopenmpt/libopenmpt_cxx.cpp",
   "../../libopenmpt/libopenmpt_ext.cpp",
   "../../libopenmpt/libopenmpt_impl.cpp",
  }
	resdefines {
		"MPT_BUILD_VER_FILENAME=\"" .. mpt_projectname .. ".dll\"",
		"MPT_BUILD_VER_FILEDESC=\"" .. mpt_projectname .. "\"",
	}
	configuration "DebugShared or ReleaseShared"
		defines { "LIBOPENMPT_BUILD_DLL" }
		resincludedirs {
			"$(IntDir)/svn_version",
			"../../build/svn_version",
			"$(ProjDir)/../../build/svn_version",
		}
		files {
			"../../libopenmpt/libopenmpt_version.rc",
		}
		resdefines { "MPT_BUILD_VER_DLL" }
	configuration {}

  flags { "Unicode" }
  flags { "ExtraWarnings" }
  defines { "LIBOPENMPT_BUILD" }
	defines { "MPT_ENABLE_DLOPEN" }
  links {
   "vorbis",
   "ogg",
   "zlib",
  }
  prebuildcommands { "..\\..\\build\\svn_version\\update_svn_version_vs_premake.cmd $(IntDir)" }
