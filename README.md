# Conqueror

### 2018 Programming Methodology 001 Team Term Project

Splix.io-like territory expansion game using OpenGL

> Team 37<br>
2017-16751 김영민<br>
2015-11514 전민재


## Design

Inspired by [paper.io](http://paper-io.com).

[paper.io](http://paper-io.com)로부터 영감을 받았습니다.


## OpenGL

Supports old GLUT and freeglut. However, MSAA doesn't properly work with old GLUT, so lines may appear rough. The library path should be set as an environment variable `OPENGL_DIR` and `%OPENGL_DIR%\bin` (or `%OPENGL_DIR%\dll`) should be added to the `PATH`. Visual Studio automatically detects its type and imports the appropriate property sheet to use the library.

구 GLUT과 freeglut을 지원합니다. 그러나 구 GLUT은 MSAA가 정상적으로 작동하지 않아 선이 거칠게 보일 수 있습니다. 라이브러리 경로는 `OPENGL_DIR` 환경변수로 설정되어 있어야 하며, `%OPENGL_DIR%\bin`(또는 `%OPENGL_DIR%\dll`)는 `PATH`에 추가되어야 합니다. Visual Studio는 라이브러리 종류를 자동으로 감지하여, 알맞은 속성 시트를 사용합니다.


## Sound

Uses [irrKlang](https://www.ambiera.com/irrklang/) (free for non-commercial use). The library is available for download at [irrKlang Downloads](https://www.ambiera.com/irrklang/downloads.html). Its path should be structured as below and set as an environment variable `IRRKLANG_DIR`, and `%IRRKLANG_DIR%\bin` should be added to the `PATH`. Visual Studio automatically detects its presence and imports a property sheet to use the library.

Soundtracks are extracted from `Tetris`.

[irrKlang](https://www.ambiera.com/irrklang/) 라이브러리(비영리 목적 사용 무료)를 사용합니다. 라이브러리는 [irrKlang Downloads](https://www.ambiera.com/irrklang/downloads.html)에서 다운로드가 가능합니다. 라이브러리 경로는 아래와 같이 이루어져 있어야 하며 `IRRKLANG_DIR` 환경변수로 설정되어 있어야 하고, `%IRRKLANG_DIR%\bin`가 `PATH`에 추가되어야 합니다. Visual Studio는 라이브러리 존재 여부를 자동으로 감지하여, 라이브러리를 사용하기 위한 속성 시트를 사용합니다.

사운드트랙은 `Tetris`로 부터 추출하였습니다.

```
irrKlang/
├── bin/
│   ├── irrKlang.dll
├── include/
│   └── *.h
└── lib/
    ├── irrKlang.lib
    └── irrKlang.exp
```


## Texture

Textures are loaded using [stb_image](https://github.com/nothings/stb) (public domain). It is included in the project. If error occurs, comment out `#define USE_TEXTURE` in `Constants.h`, however the game will not show victory/loss message.

텍스쳐는 [stb_image](https://github.com/nothings/stb) 라이브러리(퍼블릭 도메인)를 사용합니다. 라이브러리는 프로젝트에 포함되어 있습니다. 오류가 발생할 경우, `Constants.h`의 `#define USE_TEXTURE`를 주석 처리하면 되나, 승리/패배 화면이 표시되지 않습니다.
