import re

# IDENTIFICADOR DO CLIENTE
def valid_client_identifier(client_identifier):
    final_validity = True

    if (len(client_identifier) == 14):  # checks if client_identifier is cpf's lenght
        final_validity = check_cpf(client_identifier)

    elif (len(client_identifier) == 18):
        final_validity = check_cnpj(client_identifier)

    else:
        final_validity = False

    return final_validity

def check_cpf(cpf):
    standard_cpf = re.compile(r'^\d{3}\.\d{3}\.\d{3}-\d{2}$')

    if bool(re.match(standard_cpf, cpf)):  # correct standard
        list = []

        for i in range(14):
            if cpf[i] != '-' and cpf[i] != '.':
                list.append(int(cpf[i]))

        # VALIDATING FIRST DIGIT
        # STEP 1
        sum = 0
        cont = 10
        for u in range(9):
            sum = sum + (cont * list[u])
            cont = cont - 1

        # STEP 2
        new_sum = 11 - (sum % 11)

        # STEP 3
        if new_sum != list[9]:  # checks if first sum is equals to first digit after "-" in cpf
            return False

        # VALIDATING SECOND DIGIT
        # STEP 1
        sum2 = 0
        cont2 = 11
        for u in range(10):
            sum2 = sum2 + (cont2 * list[u])
            cont2 = cont2 - 1
        # STEP 2
        new_sum2 = 11 - (sum2 % 11)

        # STEP 3
        if new_sum2 != list[10]:  # checks if second sum is equals to second digit after "-" in cpf
            return False

        return True
    
    else:
        return False

def check_cnpj(cnpj):
    standard_cnpj = re.compile(r'^\d{2}\.\d{3}\.\d{3}\/\d{4}\-\d{2}$')

    if bool(re.match(standard_cnpj, cnpj)):  # correct standard
        cnpj_list = []
        support_list = [5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2]
        support_list_step2 = [6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2]

        # VALIDATING FIRST DIGIT
        # STEP 1
        for i in range(18):
            if cnpj[i] != '-' and cnpj[i] != '.' and cnpj[i] != '/':
                cnpj_list.append(int(cnpj[i]))
        sum = 0
        for i in range(12):
            sum = sum + (cnpj_list[i] * support_list[i])

        # STEP 2
        checker = sum % 11
        if checker < 2:
            checker = 0
        else:
            checker = 11 - checker
        if checker != cnpj_list[12]:
            return False

        # VALIDATING SECOND DIGIT
        # STEP 1
        sum2 = 0
        for i in range(13):
            sum2 = sum2 + (cnpj_list[i] * support_list_step2[i])

        # STEP 2
        checker2 = sum2 % 11
        if checker2 < 2:
            checker2 = 0
        else:
            checker2 = 11 - checker2

        if (checker2 != cnpj_list[13]):
            return False

        return True
    
    else:
        return False


# LISTA DE CHAVES

def valid_key_list(key):
    final_validity = True

    if key[0] == "+":
        final_validity = check_telefone(key)
    
    elif key[2] == ".":
        final_validity = check_chave_rapida(key)

    elif key[0].isalpha():
        final_validity = check_email(key)

    else:
        final_validity = False
    
    return final_validity


def check_email(email):
    standard_email = re.compile(r'^[a-z A-Z]*[a-z A-Z 0-9]+\@[a-z A-Z 0-9]+\.[a-z A-Z 0-9]+')

    if bool(re.match(standard_email, email)):
        return True
    
    else:
        return False


def check_chave_rapida(key):
    standard_key = re.compile(r'[a-f A-F 0-9]{2}\.[a-f A-F 0-9]{2}\.[a-f A-F 0-9]{2}\.[a-f A-F 0-9]{2}')

    list = []
    cont = 0

    if bool(re.match(standard_key, key)):

        for i in range(11):
            if key[i] != '.':
                list.append(key[i])

        while cont < 8:
            if key[cont] == key[cont+1]:
                return False
            else:
                cont += 2

        return True
    
    else:
        return False


def check_telefone(number):
    standard_value = re.compile(r'\+55\(\d{2}\)\d{4}\-\d{4}')

    check_begin = re.match(standard_value, number)

    if check_begin:
        return True
    
    else:
        return False
    
    
# SEPARADOR "=========="
def check_separador(separator):
    standard_separator = re.compile(r'\={10}$')

    if bool(re.match(standard_separator, separator)):
        return True
    
    else:
        return False
    
# LISTA DE TRANSAÇÕES
def check_source_key(source_key):
    cont = 0

    for valid_keys in valid_keys_list:
        if valid_keys == source_key:
            # Guarda o valor da posição da source key no local [0] do vetor de posições:
            startpos_keys_list[0] = cont
            return True
        cont += 1

    return False

def check_target_key(target_key):
    cont = 0

    for valid_keys in valid_keys_list:
        if valid_keys == target_key:
            for i in range(1, len(startpos_keys_list)):
                # Compara as posições da source_key e da target_key com a posição de início do próximo cliente:
                if cont < startpos_keys_list[i] and startpos_keys_list[0] < startpos_keys_list[i]:
                    return False    
                else:
                    return True
        cont += 1

    return False

def check_value(value):
    standard_value = re.compile(r'^[R]\$ \d*,+\d{2}$')

    check_value = re.match(standard_value, value)

    if check_value:
        return True
    else:
        return False
    
def check_timestamp(timestamp):
    standard_timestamp = re.compile(r'\d{2}/\d{2}/\d{4} \d{2}\:\d{2}$')

    check_timestamp = re.match(standard_timestamp, timestamp)

    if check_timestamp:
        return True
    else:
        return False
    
def check_security_code(security_code):
    check_security_code = True

    cont_upperg = 0
    cont_digits = 0
    cont_special_char = 0
    cont_lowerg = 0

    standard_upperg = re.compile(r'[A-Z]')
    standard_digits = re.compile(r'[0-9]')
    standard_lowerg = re.compile(r'[a-z]')

    for char in security_code:
        check_security_code = re.match(standard_upperg, char)
        if check_security_code:
            cont_upperg += 1

        check_security_code = re.match(standard_digits, char)
        if check_security_code:
            cont_digits += 1

        if char == "$" or char == "@" or char == "%" or char == "(" or char == "*":
            cont_special_char += 1
        
        check_security_code = re.match(standard_lowerg, char)
        if check_security_code:
            cont_lowerg += 1
    
    if cont_upperg == 3 and cont_digits == 4 and cont_special_char == 2 and cont_lowerg == 3:
        return True
    else:
        return False


# MAIN
# lote -> listaCliente -> identificadorCliente(cpf/cnpj) / listaChaves(email/rapida/telefone)
#     -> separador
#     -> listaTransações -> origem / destino / valor / timestamp

# CPF : CPFs do tipo 111.111.111-11 ; 222.222.222-22 ... são aceitos pelo algoritmo, mas não existem! (Devo tirar?)

# INÍCIO
# Loop para receber e avaliar todos os clientes e seus dados, até encontrar a divisória "==========":

first_validation = True
second_validation = True

# Variável que contará até a posição da última chave de um cliente:
count = 0
# Lista que guardará as chaves válidas dos clientes inseridos:
valid_keys_list = []

# Lista que guardará a posição "înicial" em que as chaves de um novo cliente estão guardadas na lista de chaves 
# válidas acima (A primeira posição [0] será reservada para futura validação de cliente origem e destinatário):
startpos_keys_list = [0]

while True:
    client = input()

    client_data = client.split(" ")

    client_identifier = client_data[0]

    if client_identifier[0] == "=":
        break
    
    else:
        first_validation = valid_client_identifier(client_identifier)

        # Identificação do cliente inválida:
        if not first_validation:
            break

        valid_keys_list.append(client_identifier)
        count += 1

        del client_data[0]

        for client_key in client_data:
            first_validation = valid_key_list(client_key)

            if first_validation:
                valid_keys_list.append(client_key)
                count += 1

            else:
                break

        if not first_validation:
            break

        startpos_keys_list.append(count)

if not first_validation:
    print(False)

# PARTE 2:
# Novo loop para receber e avaliar as transações entre os clientes, até receber o último input:

else:
    while True:
        transaction = input()

        transaction_data = transaction.split(" ")

        source_key = transaction_data[0]
        target_key = transaction_data[1]
        value = transaction_data[2] + " " + transaction_data[3]
        timestamp = transaction_data[4] + " " + transaction_data[5]
        security_code = transaction_data[6]

        second_validation = check_source_key(source_key)

        if not second_validation:
            break

        second_validation = check_target_key(target_key)

        if not second_validation:
            break

        second_validation = check_value(value)

        if not second_validation:
            break

        second_validation = check_timestamp(timestamp)

        if not second_validation:
            break

        second_validation = check_security_code(security_code)

        if not second_validation:
            break

        break

    if not second_validation:
        print(False)
    else:
        print(True)

# CASO DE TESTE BASE (True):

# 136.775.118-79 pmlxew@veracg.com +55(92)3584-0188
# 90.400.888/0001-42 D5.D9.A9.b6
# ==========
# pmlxew@veracg.com 90.400.888/0001-42 R$ 100,00 11/12/2022 18:06 @@XHn6az31O9
# D5.D9.A9.b6 +55(92)3584-0188 R$ 25,89 13/01/2022 10:21 W1%U(7od43Li

# 04.280.196/0001-76 uea@uea.edu.br +55(92)3348-7601
# 09.628.825/0001-20 03.A4.2B.F8
# ==========
# uea@uea.edu.br 09.628.825/0001-20 R$ 1.000.000,00 09/01/2023 09:03 ABC@@1234abc
# 03.A4.2B.F8 +55(92)3348-7601 R$ 2.000.000,00 08/01/2022 10:10 FG@H*12ab34c


