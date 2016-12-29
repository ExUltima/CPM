```json
{
  "properties": {
    "toolchain_independent": true
  },
  "settings": {
    "litever": {
      "type": "bool",
      "default": false,
      "when": {
        "true": {
          "define": [""],
          "undefine": []
        },
        "false": {
          "define": [""],
          "undefine": [""]
        }
      }
    }
  },
  "build": {
    "*": {
      "define": ["LIBEAY=1"],
      "undefine": ["COMPAT"]
    },
    "win32": {
      "engine": "msbuild",
      "params": {
        "solution": "src/solution.sln",
      },
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
  },
  "dependencies": {
    "*": [
      {
        "url": "github://ExUltima/WinTL"
      }
    ],
    "win32": [
      {
        "url": "github://openssl/openssl"
      }
    ],
    "posix": [
      {
        "url": "github://jamwt/libtask",
        "settings": {
          "use_setjump": true
        }
      }
    ],
    "linux": [
      {
        "url": "system://libssl"
      }
    ]
  }
}
```
