FILE(REMOVE_RECURSE
  "../src/laser_to_wall/msg"
  "../msg_gen"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/WallScan.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_WallScan.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
