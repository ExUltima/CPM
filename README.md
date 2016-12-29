```json
{
  "build": [
    "win32": {
      "engine": "msbuild",
      "params": {
        "solution": "src/solution.sln",
        "hooks": [
          {
            "engine": "msvc-setter"
          },
          {
            "engine": "command-executer",
            "params": {
              "prebuild": {
                "directory": "scripts",
                "command": "prebuild.bat"
              },
              "postbuild": {
                "directory": "scripts",
                "command": "postbuild.bat"
              }
            }
          }
        ]
      }
    }
  ],
  "dependencies": {
    "*": [
      "github://ExUltima/WinTL"
    ],
    "win32": [
      "github://openssl/openssl"
    ],
    "posix": [
      "github://jamwt/libtask"
    ],
    "linux": [
      "system://libssl"
    ]
  }
}
```
