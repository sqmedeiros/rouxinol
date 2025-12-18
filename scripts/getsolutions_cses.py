from selenium import webdriver 
from selenium.webdriver.common.by import By
import time
import re
import random
import numpy as np
import os



linguagem = 5 #8 python, 5 java, 2 C, 3 C++
solutions_per_page = 30
pegar_n_solucoes = 2 #solucoes de cada problema a serem extraidas
lista_problemas = [
   "1071",
   "1082",
]
# lista_problemas = [
#   "1071",
#   "1082",
#   "1084",
#   "1140",
#   "1158",
#   "1621",
#   "1632",
#   "1634",
#   "1635",
#   "1636",
#   "1639",
#   "1640",
#   "1642",
#   "1643",
#   "2185",
#   "1091",
#   "1131",
#   "1132",
#   "1190",
#   "1192",
#   "1195",
#   "1197",
#   "1619",
#   "1628",
#   "1666",
#   "1667",
#   "1668",
#   "1669",
#   "1671",
#   "1672",
#   "1674",
#   "2166"
# ]

def fazLogin(driver,usuario, senha):
    username_field = driver.find_element(By.NAME, "nick")
    password_field = driver.find_element(By.NAME, "pass")
    username_field.send_keys(usuario)
    password_field.send_keys(senha)
    submit_button = driver.find_element(By.CSS_SELECTOR, 'input[type="submit"][value="Submit"]')
    submit_button.click()
    time.sleep(0.5)

def extrai_codigo(driver):
    

    code_element = driver.find_element(By.CSS_SELECTOR, "pre.prettyprint.linenums")
    html = code_element.get_attribute("outerHTML")
    # print(html)
    
    #substitui linhas em branco por uma sequencia especial
    padrao = r'<div class="L(\d+)"><span class="pln">\s+</span></div>'
    html = re.sub(padrao,r'<div class="L\1"><span class="pln">#!@</span></div>',html)
    
    #cria novo driver com html modificado
    driver.execute_script("document.write(arguments[0]);", html)
    driver.execute_script("document.close();") # Finish writing the page
    code_element = driver.find_element(By.CSS_SELECTOR, "pre.prettyprint.linenums")
    
    #extrai texto e substitiu sequencia especial com quebra de linha
    code_text = code_element.text
    code_text = code_text.replace('#!@','')
    return code_text
    

def pega_solucao(driver,link):
    driver.get(link)
    codigo = extrai_codigo(driver)
    return codigo

def extrai_nome(link):
    index_position = link.find("entry")
    nome = link[index_position+6:-1] 
    if linguagem == 5:
        nome = 'entry_' + nome + '.java'
    if linguagem == 8:
        nome = nome + ".py"
    return nome

def sem_extensao(nome):
    i = nome.find('.')
    return nome[0:i]

def salva_codigo(problema,nome,codigo):
    #cria diretorio caso nao exista
    os.makedirs(problema, exist_ok=True)
    #acha nome sem extensao
    nome_sem_extensao = sem_extensao(nome)
    if linguagem == 5:
        codigo = codigo.replace('public static void main','public static void ' + nome_sem_extensao)
    with open(problema + '/' + nome, 'w', encoding="utf-8") as f:
        f.write(codigo)
        
def extrai_numero_solucoes(problema,driver):
    pagina = 1
    driver.get("https://cses.fi/problemset/queue/" + problema + "/" + str(pagina) + "/?lang="+str(linguagem)+"&status=2&user=&by=0&order=1")
    nsol = driver.find_element(By.XPATH, "//p[contains(., 'Number of submissions:')]")
    s = nsol.text
    i = s.find(":")
    return int(s[i+1:])

def pega_lista_solucoes(problema,pagina,driver):
    driver.get("https://cses.fi/problemset/queue/" + problema + "/" + str(pagina) + "/?lang="+str(linguagem)+"&status=2&user=&by=0&order=1")
    #localiza a lista de hrefs 
    link_solucoes = driver.find_elements(By.CLASS_NAME, "details-link")

    lista_solucoes = []
    for element in link_solucoes:
        href = element.get_attribute("href")
        if href:
            lista_solucoes.append(href)
    return lista_solucoes

def sorteia(page_last_solution, solucoes_sorteadas):
    pagina = random.randint(1, page_last_solution)
    solution = random.randint(0, solutions_per_page-1)
    while [pagina,solution] in solucoes_sorteadas:
        pagina = random.randint(1, page_last_solution)
        solution = random.randint(0, solutions_per_page-1)
    solucoes_sorteadas.append([pagina,solution])
    return pagina, solution

def salva_lista_solucoes_sorteadas(problema,solucoes_sorteadas):
    with open(problema + '/' + 'lista_sorteadas.txt', 'a') as f:
        for l in solucoes_sorteadas:
            f.write(str(l) + '\n')


#inicia navegador
driver = webdriver.Chrome() 
driver.get("https://cses.fi/login")
time.sleep(1)

fazLogin(driver,"sqmedeiros","Mmarcelo52")

for problema in lista_problemas:
    
    solucoes_sorteadas = []

    #entra no problema atual, na primeira pagina para pegar o numero de solucoes que tem
    print('acessando o problema  ' +  problema )
    n_solucoes = extrai_numero_solucoes(problema,driver)
    print(str(n_solucoes) + " achadas")
    page_last_solution = int(np.floor(n_solucoes/solutions_per_page))
    
    cont = 1
    for i in range(pegar_n_solucoes):
        print('Extraindo solucao ' + str(cont))
        pagina, solution = sorteia(page_last_solution, solucoes_sorteadas)     
        lista_solucoes_pagina_atual = pega_lista_solucoes(problema,pagina,driver)
        link = lista_solucoes_pagina_atual[solution]
        codigo = pega_solucao(driver, link)
        nome = extrai_nome(link)
        solucoes_sorteadas.append(nome)
        salva_codigo(problema,nome,codigo)
        cont += 1
    salva_lista_solucoes_sorteadas(problema,solucoes_sorteadas)


