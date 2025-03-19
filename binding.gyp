{
  "targets": [
    {
      "target_name": "binding",
      "sources": [
        "src/binding.cc",
        "src/memcache.cc",
        "src/bson.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++",
        "MACOSX_DEPLOYMENT_TARGET": "10.7"
      },
      "msvs_settings": {
        "VCCLCompilerTool": { "ExceptionHandling": 1 }
      },
      "conditions": [
        [
          "OS==\"linux\"",
          {
            "link_settings": {
              "libraries": [
                "-lrt"
              ]
            }
          }
        ]
      ]
    }
  ]
}
