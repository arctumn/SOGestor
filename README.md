# SOGestor

[![Run on Repl.it](https://repl.it/badge/github/arctumn/SOGestorCurrently)](https://repl.it/github/arctumn/SOGestorCurrently)

## Parte1

[Source Code Parte 1](https://github.com/arctumn/SOGestor/tree/Vers%C3%A3o-parte1-codigo-N%C3%83O-DAR-MERGE)

      

## Tasks concluidos

- [x] -> parser feito com teste
- [x] -> Executor de instruções (Provavelmente apenas FIFO)
- [x] -> Executor de programas metodo não preemptivo (FIFO)
- [x] -> Makefile
- [x] -> Teste para modo não preemptivo (FIFO)
- [x] -> Relatorio parte1(fifo implementado)
- [ ] -> Executor de programas metodo preemptivo (SJF)
- [ ] -> adicionar outros


## Hiperligaçoes

[valgrind](http://valgrind.org/) -> Otimo verificador de erros de memoria para usar valgrind ./(nome do executavel)

[Aprender a usar o git](https://rogerdudler.github.io/git-guide/) -> Otimo guia para aprenderem a usar git

[Memes](https://www.reddit.com/r/memes/) -> DONT LET YOUR MEMES BE DREAMS

[Repl.it](https://repl.it/) -> Usar isto para ser fácil programar em conjunto

## Makefile

Regras para usar o Makefile:
```
make // compila tudo
make clean // limpa tudo
make cleanEx // limpa objetos este ta incorporado no make para remover os ficheiros .o criados pelo make
```
## bugFixes

Teste feito um dos bugs devia ao = estar a passar apenas o endereço levando a que mostras-se mas nao salvava o contuodo, a solução que arrangei envolve usar o strdup que permite copiar o contuedo.(1)


```
(1)
// versao correta
 while(fgets(string,sizeof(string),fp1) != 0){
        arraydestrings[i] = strndup(string,sizeof(string)); // fix copia o conteudo em vez do endereço
        printf("%s",arraydestrings[i]);
        i++;
    }
 //versao faulty abaixo
  while(fgets(string,sizeof(string),fp1) != 0){
        arraydestrings[i] = string; // aparenta estar correto a primeira vista mas fora do while apenas ira mostrar o ultimo conteudo
        printf("%s",arraydestrings[i]);
        i++;
    }
```


Deparei-me tambem que a forma que estavamos a criar o array de instruções era "faulty", ou seja copiava vezes a mais, isto acontecia pq tinhamos varios ifs para o mesmo conteudo.(2)

```
(2)
// Ter mais que um destes apenas cria duplicados
if(!(strncmp(arraydestrings[i],"I:",strlen("I:")))){
            char *I = strtok(arraydestrings[i],"I:");
            arrayFinalStrings[c] = I;
            c++;
        }
```





## Explicações de markdown by arctumn

 ```  
 DEIXAR DOIS OU MAIS ESPAÇOS EM MARKDOWN SIGNIFICA PARAGRAFO
 [x] -> concluido 
 [ ] -> por concluir
 #   -> representa um titulo, ## um sub titulo .... n# n subtitulo Deixar um espaço apos o #
 [.....](aaaa.aaa) -> É o template para a hiperligaçao aaaa.aaa
EXEMPLO DE UMA HIPERLIGAÇAO
[Jar com a Classe Ler](https://github.com/arctumn/POOProject/blob/master/myinputs.jar) -> Jar com o Ler 1º Semestre para interessados
 Existem mais mas não acho que sejam precisos
 ```
