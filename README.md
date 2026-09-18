# IDJ 2026

Projeto desenvolvido para a disciplina de Introducao ao Desenvolvimento de Jogos.

**Aluna:** Esther Sena Martins  
**Matricula:** 211062769

## Requisitos

- Compilador C++ com suporte a C++17
- SDL2
- SDL2_image
- SDL2_mixer
- `pkg-config`
- `make`

No Ubuntu/Debian, as dependencias podem ser instaladas com:

```bash
sudo apt install build-essential make pkg-config libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
```

## Como executar

Na pasta raiz do projeto, compile:

```bash
make
```

Em seguida, execute o jogo:

```bash
./game
```

Os arquivos de imagem devem permanecer em `Recursos/img` e os arquivos de audio em `Recursos/audio`.
