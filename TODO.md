

### DATA ###

    O programa é capaz de copiar um diretório inteiro.

    Próximos passos:

    - Criar uma pasta principal que conterá os backups que forem feitos
        Formato desta pasta:

        BACKUPS
            - backup 1
            - backup 2
            - backup 3
            - backup n

        Essa pasta será um padrão. Deve ser criada quando o programa rodar pela primeira vez.

        - Cada backup terá como nome a data do dia
        

    - O usuário deve ser capaz de adicionar e remover caminhos pelo próprio programa. (Feito)

    - Falta remover.

    - Depois de adicionar a capacidade de remover, criar o procedimento de backup.

    - TESTAR CONSEGUIR ARQUIVOS!!!!! (testado e funcionando)

#### REFATORAÇÃO ####

- (*) Modificar o sistema de adicionar arquivos para backups. Deve ser um pequeno CRUD.
    - Adicionar arquivos
    - Remover arquivos
    - Mostrar arquivos

- Verificar e refatorar, se necessário, a arquitetura de cada um dos sistemas:
    - Arquivos (*)
    - Caminhos
    - Backups
    - Uteis
    - Algoritimo de "main"
