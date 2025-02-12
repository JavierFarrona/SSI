# SSI

Repositorio para la asignatura de Seguridad en Sistemas Informáticos (SSI) del tercer año (It 5) de Ingeniería Informática en la Universidad de La Laguna (Año 2024-2025).

## Descripción

Este repositorio contiene el código y los recursos utilizados en las prácticas de la asignatura de SSI. El objetivo de estas prácticas es aprender y aplicar conceptos de criptografía y seguridad informática.

## Estructura del Proyecto

- `lib/`: Contiene las bibliotecas y archivos de cabecera utilizados en el proyecto.
- `src/`: Contiene el código fuente de las prácticas.
- `README.md`: Este archivo, que proporciona una visión general del proyecto.

## Prácticas

### Práctica 1: Introducción a la Criptografía
- Descripción: Implementación de algoritmos básicos de criptografía.
- Archivos: `src/practica1.cc`, `lib/crypto.h`

### Práctica 2: Cifrado de Bloques
- Descripción: Implementación y análisis de cifrados de bloques como AES.
- Archivos: `src/practica2.cc`, `lib/aes.h`

### Práctica 3: Cifrado de Flujo
- Descripción: Implementación del cifrado de flujo ChaCha20.
- Archivos: `src/chacha20.cc`, `lib/chacha20.h`, `src/main.cc`

## Compilación y Ejecución

Para compilar y ejecutar el código, puedes usar el siguiente comando en la raíz del proyecto:

```sh
make
./bin/main
