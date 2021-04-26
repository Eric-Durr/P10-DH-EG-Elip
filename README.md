# SSI P08 - IMPLEMENTACIÓN DEL CIFRADO DE ElGamal


**Estructura del repositorio:**

```
prct06-AES/
├─ docs/                                        # Project documentation folder
├─ include/                                     # Library files folder
│  ├─ Catch2/catch.h                            ## C++ TDD testing framework
├─ src/                                         # Source files folder
├─ test/                                        # Test files folder
├─ .gitignore                                   # Ignored files git config file
├─ makefile                                     # C++ tasks automation file
├─ Doxyfile                                     # Doxygen configuration file 
├─ PracticaElGamal.pdf                          # P08 - assignment
├─ README.md                                    # Front repository information file
```

**Uso**

**Compilación del ejecutable**

```bash
$ make
```

**Ejecución del programa**

```bash
$ ./el_gamal <prime number> <a integer> <k secret> <x secret> <message number>

```

**Ejemplo sin traza**

```
./el_gamal 13 4 5 2 8

CIFRADO DE INTERCAMBIO DE CLAVES - ELGAMAL

Entrada: p = 13, a = 4, k = 5, x = 2, m = 8
Salida: Ya=10, Yb=3, K=9, C=7, K^(-1) = 3, M=8
```


**Referencias y enlaces:**

- [Enlace al repositorio](https://github.com/Eric-Durr/P08-ElGamal)


**Licencia**

[MIT](https://choosealicense.com/licenses/mit/)

**Autoría**

- Eric Dürr Sierra - [alu0101027005](alu0101027005@ull.edu.es)

