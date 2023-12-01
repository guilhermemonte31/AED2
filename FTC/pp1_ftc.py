import re

#IDENTIFICADOR DO CLIENTE
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
        new_sum = (sum * 10) % 11

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
        new_sum2 = (sum2 * 10) % 11

        # STEP 3
        if new_sum != list[10]:  # checks if second sum is equals to second digit after "-" in cpf
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


#LISTA DE CHAVES

def valid_key_list(key_list):
    print("t")

def check_email(email):
    standard_email = re.compile(r'^[a-zA-Z]+@[a-zA-Z]+\.+[a-zA-Z]+$')
    if bool(re.match(standard_email, email)):
        return True
    else:
        return False


def check_chave_rapida(key):
    standard_key = re.compile(r'[A-F0-9]{2}\.[A-F0-9]{2}\.[A-F0-9]{2}\.[A-F0-9]{2}')
    list = []
    cont = 0
    if bool(re.match(standard_key, key)):
        for i in range(11):
            if key[i] != '.':
                list.append(key[i])
        while cont <8:
            if key[cont] == key[cont+1]:
                return False
            else:
                cont += 2
        return True
    else:
        return False


def check_telefone(number):
    standard_number = re.compile(r'\+55\(\d{2}\)\d{4}\-\d{4}')
    check_begin = re.match(standard_number, number)
    if check_begin:
        return True
    else:
        return False
    
    
#SEPARADOR
def check_separador(separator):
    standard_separator = re.compile(r'\={10}$')
    if bool(re.match(standard_separator, separator)):
        return True
    else:
        return False
    





#
# MAIN
# lote -> listaCliente -> identificadorCliente(cpf/cnpj) / listaChaves(email/rapida/telefone)
#     -> separador
#     -> listaTransações -> origem / destino / valor / timestamp
lote = input()
# parts = lote.split("\n")
# client_list = parts[0]
# client_list_parts = client_list.split(' ')
# client_identifier = client_list_parts[0]
# print(valid_client_identifier(client_identifier))
#
# key_list = parts[0]
# valid_key_list(key_list)
# check_email(lote)
#print(check_chave_rapida(lote))
print(check_separador(lote))

