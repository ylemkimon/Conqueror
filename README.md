# Conqueror

### 2018 Programming Methodology 001 Team Term Project

Splix.io-like territory expansion game using OpenGL

> Team 37<br>
2017-16751 김영민<br>
2015-11514 전민재

## Design

Inspired by [paper.io](http://paper-io.com).

[paper.io](http://paper-io.com)로부터 영감을 받았습니다.


## Sound

Uses [irrKlang](https://www.ambiera.com/irrklang/) (free for non-commercial use). Library path should be set as an environment variable `IRRKLANG_DIR`, `%IRRKLANG_DIR%\bin` should be added to the `PATH`. Visual Studio automatically detects its presence and imports a property sheet to use the library.

Soundtracks are extracted from `Tetris`.

[irrKlang](https://www.ambiera.com/irrklang/) 라이브러리(비영리 목적 사용 무료)를 사용합니다. 라이브러리 경로는 `IRRKLANG_DIR` 환경변수로 설정되어 있어야 하며, `%IRRKLANG_DIR%\bin`가 PATH에 추가되어야 합니다. Visual Studio는 존재를 자동으로 감지하여, 라이브러리를 사용하기 위한 속성 시트를 사용합니다.

사운드트랙은 `Tetris`로 부터 추출하였습니다.


## Texture

Textures are loaded using [stb_image](https://github.com/nothings/stb) (public domain). It is included in the project. If error occurs, comment out `#define USE_TEXTURE` in `Constants.h`, however the game will not show Win/Lose message.

텍스쳐는 [stb_image](https://github.com/nothings/stb) 라이브러리(퍼블릭 도메인)를 사용합니다. 라이브러니는 프로젝트에 포함되어 있습니다. 오류가 발생할 경우, `Constants.h`의 `#define USE_TEXTURE`를 주석 처리하면 되나, 그렇게 하면 게임은 승리/패배 화면을 출력하지 않습니다.
