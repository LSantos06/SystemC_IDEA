# [IDEA](https://github.com/LSantos06/SystemC_IDEA)
## Trabalho Final de Modelagem de Sistemas em Silício 1/2017
O trabalho consiste em implementar, utilizando a linguagem _SystemC_, um módulo de criptografia que utiliza o __IDEA__ (_International Data Encryption Algorithm_) que é um algoritmo de cifra de bloco (simétrica) que faz uso de uma _chave secreta_ de 128 bits e tanto o _texto legível_ (entrada) quanto o _texto ilegível_ (saída) possuem 64 bits. O algoritmo é usado tanto para a cifragem quanto para a decifragem.

#### Impelementação
No resultado final da implementação: O membro Lucas Nascimento codificou a estrutura do módulo em _SystemC_, definindo os registradores, os processos e as funções utilizadas no módulo como por exemplo a implementação dos rounds e half-round, realizando também a parte dos testes do módulo para a verificação do projeto. O membro Lucas Avelino implementou principalmente a conexão do módulo com a _Network on Chip_, realizando também parte da geração das sub-chaves. O projeto foi implementado em alto nível, utilizando loops ao invés de módulos de round e half-round, que podem ser utilizados no futuro. Mais detalhes sobre a implementação do projeto e as tarefas de cada um estão no _GitHub_ do projeto: https://github.com/LSantos06/SystemC_IDEA.

#### Grupo
* Lucas Avelino
  * Matrícula: 13/0013072
  * GitHub: [lucasavelino](https://github.com/lucasavelino)
* Lucas Nascimento
  * Matrícula: 14/0151010
  * GitHub: [LSantos06](https://github.com/LSantos06)

#### Operações Básicas
O _IDEA_ possui três grupos algébricos cujas operações são misturadas. Estas operações, que podem ser facilmente implementadas via hardware e/ou software, são:
- ![#f03c15](https://placehold.it/15/f03c15/000000?text=+) `Multiplicação módulo 2¹⁶+1 (multiplicação ignorando qualquer overflow);`
- ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) `Adição módulo 2¹⁶ (adição ignorando qualquer overflow);`
- ![#1589F0](https://placehold.it/15/1589F0/000000?text=+) `Xor.`

Todas estas operações são feitas com blocos de 16 bits, o que faz com que este algoritmo também seja eficiente em processadores de 16 bits.

#### Geração das sub-chaves
A partir da _chave secreta_ de 128 bits, são geradas 52 _sub-chaves_ de 16 bits. Cada _round_ utiliza 6 _sub-chaves_, totalizando 48 _sub-chaves_, mais 4 _sub-chaves_ são geradas para a realização do _half-round_.

#### Round e Half-round
<p align="center">
  <img src="img/IDEA_round.png">
  <br>
  <t><b>Figura 1</b>: Um <i>round</i> de criptografia do IDEA (Repetido 8 vezes).</t>
  <br>
</p>

<p align="center">
  <img src="img/IDEA_half_round.png">
  <br>
  <t><b>Figura 2</b>: <i>Round final</i> (<i>half-round</i>) de criptografia do IDEA.</t>
  <br>
</p>

#### Referências
* [ivansarno](https://github.com/ivansarno/IDEA-cipher)
* [Roudo Terada (DCC-USP) 1999](https://github.com/LSantos06/SystemC_IDEA/blob/master/IDEA.pdf)
* [Quadibloc](http://www.quadibloc.com/crypto/co040302.htm)
* [Numaboa](http://www.numaboa.com.br/criptografia/bloco/336-idea?showall=&start=4)
