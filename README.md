Pokretanje primjera
===================

Dostupni primjeri:
- NONE - bez makro koda, za usporedbu veličine egzekutabilca
- SIMPLE - jednostavan primjer sa listom integera i listom listi integera
- SORT - primjer sortiranja liste floatova
- FILTER - primjer filtera preko liste integera
- MAP - primjer mapa preko liste doublova
- REDUCE - primjer reducea preko liste struktura vektora
- POINTERS - primjer sa pointerima na custom strukturu
- WTF - map preko map - reduceanog map-a po indeksima liste brojeva

```sh
cd ./Code

clang -D{example} main.c -o macros && ./macros
# -- ili --
gcc -D{example} main.c -o macros && ./macros

# pokretanje WTF example-a
{clang, gcc} -DWTF main.c -o macros && ./macros

# pregledavanje expandanog koda (ne expanda __LINE__, __FILE__ i __FUNCTION__)
{clang, gcc} -DWTF -E main.c | less
```

- Types.h sadrži helper code i typedefove za neke ugrađene tipove (npr unsigned int -> UInt) i definiciju Show makroa
- List.h sadrži implementaciju array liste (ustvari extendible arraya) i 'funkcija' koje operiraju nad tom listom
- main.c sadrži entripoint u egzekutabilac i implementacije primjera


Ako itko ima ikakvih zamjerki ili ispravki ili uoči propust/nelogičnost, bio bih jako zahvalan da mi javi pa da to ispravim na domagoj.cerjan@gmail.com :)
