# Máquina de Turing em C

## Apresentação em vídeo no link a seguir
[Clique aqui para assistir](https://youtu.be/IQuMPt585wc)

## Objetivo

Desenvolva um programa que simule uma Máquina de Turing genérica. O programa receberá como entrada um arquivo de texto com a seguinte estrutura:

1. Na primeira linha, os símbolos do alfabeto de entrada (Σ) devem ser especificados, com letras em minúsculo, sem espaços entre eles, e concatenados com símbolos do alfabeto da fita (Γ). Não deve haver o símbolo de espaço em branco ⊔. Limite de 30 símbolos na primeira linha.

2. Na segunda linha, informe o número de estados. Por simplicidade, o estado de aceitação sempre será o último estado. Por exemplo, na Máquina M1, o estado de aceitação (qaceita) é 5. Considere que o estado inicial será sempre o primeiro estado e que uma máquina terá, no máximo, 50 estados.

3. Na terceira linha, indique o número 'n' de transições da máquina. Nas próximas 'n' linhas, forneça as transições no seguinte formato, separado por espaços em branco:
   `<estado corrente> branco <símbolo em Γ> branco <gravar na fita> branco <mover> branco <estado de chegada>`.
   As ações de mover a cabeça de leitura são representadas pelas letras 'E' (mover para a esquerda) e 'D' (mover para a direita). O símbolo em branco ⊔ será representado pelo caractere '-' (hífen).

4. Após as 'n' transições, inclua uma linha com um número inteiro que especifica quantas palavras a máquina de Turing deverá testar. As palavras estão armazenadas na fita da máquina e não devem conter espaços em branco. Cada palavra deve ser colocada em uma linha e conter símbolos do alfabeto de entrada (Σ). A fita tem um limite máximo de 100 caracteres.

Exemplo:
```
abxy
5
11
1 a x D 2
1 y y D 4
1 - - D 5
2 a a D 2
2 y y D 2
2 b y E 3
3 a a E 3
3 y y E 3
3 x x D 1
4 y y D 4
4 - - D 5
4
aabb
aaabbb
abab
bbaa
```

O programa processará a fita de acordo com as especificações fornecidas no arquivo de entrada e exibirá o resultado na tela. A saída incluirá a ordem da fita processada, a palavra lida na fita e a informação "OK" (se a máquina parou o processamento no estado de aceitação) ou "not OK" (caso contrário).

Exemplo de Saída:
```
1: aabb OK
2: aaabbb OK
3: abab not OK
4: bbaa not OK
```
