# SSI P09 - IMPLEMENTACIÓN DEL CIFRADO RSA


**Estructura del repositorio:**

```
prct09-RSA/
├─ docs/                                        # Project documentation folder
├─ include/                                     # Library files folder
│  ├─ Catch2/catch.h                            ## C++ TDD testing framework
├─ src/                                         # Source files folder
├─ test/                                        # Test files folder
├─ .gitignore                                   # Ignored files git config file
├─ makefile                                     # C++ tasks automation file
├─ Doxyfile                                     # Doxygen configuration file 
├─ Practica9RSA.pdf                             # P09 - assignment
├─ README.md                                    # Front repository information file
```

**Uso**

**Compilación del ejecutable**

```bash
$ make
```

**Ejecución del programa**

```bash
$ ./rsa <p> <q> <d>

```

**Ejemplo de ejecución**

```
./rsa 2347 347 5

----SIMULADOR DE CIFRADO RSA-----

Parámetros longroducidos:
P=2347
q=347
d=5

Comprobando paridad de p y q ...
Ambos números son pares se procede con el cifrado...
Calculando n y phi(n) ...
Comprobando primalidad de d con phi(n)=811716 ...
d=5 es primo con phi(n)=811716, se procede con el cifrado ...
Valor de clave de cifrado e=649373
Introduzca el mensaje a cifrar: amigo mio
Texto a encriptar: AMIGO MIO
Como n=814409 se divide eltexto en bloques de 4 caracteres
Bloques decimales extraidos del texto: 8326 254398
Bloques decimales cifrados: 587813 526359
```


**Referencias y enlaces:**

- [Enlace al repositorio](https://github.com/Eric-Durr/P09-RSA)


**Licencia**

[MIT](https://choosealicense.com/licenses/mit/)

**Autoría**

- Eric Dürr Sierra - [alu0101027005](alu0101027005@ull.edu.es)

