# MC504 Projeto 2 - Animação multithread com semáforos

## Grupo 
* `Fernando de Saes Madeira Vallar RA: 171509`
* `João Theophilo Morais Santos da Silva RA: 237736`
* `Lucas Barroso Alves Farias RA: 220650`

## Resumo do Projeto
> Para o segundo trabalho da disciplina, no intuito de demonstrar uma aplicação multithread com visualização e sincronização via semáfaros, decidimos abordar o conhecido caso dos multiplos Barbeiros Dorminhocos. O problema se resume ao funcionamento de uma barbearia, que no nosso caso teste possui 2 barbeiros e 5 cadeiras de espera, enquanto não tiver clientes, os barbeiros dormem, na chegada de um cliente, ele é designado a uma cadeira de espera, no caso de todas as cadeiras de espera estarem ocupadas, o cliente vai embora. Uma vez ocupando uma cadeira de espera, o cliente será designado a cadeira vazia de um dos barbeiros assim que uma ela estiver disponível, caso os dois barbeiros estejam ocupados, o cliente terá que aguardar. Ao passar para a cadeira de um dos barbeiros, o estado desta cadeira (ocupada) se manterá até que o trabalho do barbeiro acabe e o cliente saia. Todo este processo é mostrado através de um painel animado, que é exibido sempre que uma mudança ocorre, sendo que o trabalho é dividido entre threads de clientes e barbeiros, como pode ser visto no código do arquivo [projeto2.c](https://github.com/IucasF/trabalho2mc504/blob/main/projeto2.c) .
