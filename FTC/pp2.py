#{
#    'inicial':0,'aceita':1,'rejeita':2,
#    'delta':[(0,0,1,"#","D"),(0,0,0,"x","D"),(0,1,"b","b","P"),
#    (0,2,"x","x","P"), (0,0,1,"#","D")]
#}
#   (0,0,1,"#","D")
#   estado atual (0), novo estado(0), conteudo atual(1), 
#   conteudo a ser inserido(#),  movimentacao(D)
def verify_word(word, dict_tm):
    new_word = ''
    begin = dict_tm['inicial']
    accept = dict_tm['aceita']
    reject = dict_tm['rejeita']
    delta = dict_tm['delta']
    
    current_state = begin
    delta_size = len(delta)
    word_size = len(word)
    i=0
    while i<word_size: #while pra percorrer a palavra
        for j in range(delta_size):
            if current_state == delta[j][0] and str(word[i]) == str(delta[j][2]):
                current_state = delta[j][1]
                new_word += str(delta[j][3])
                if(delta[j][4] == 'D' and i<word_size):
                    i +=1
                    break
                elif delta[j][4] == 'E' and i>0:
                    i -=1
                    break
                elif delta[j][4] == 'P':
                    i +=0
                    break
    print(f"Fim estado final: {current_state} palavra final: {new_word}")
            
  
        
        

turing_machine = input()
num_words = int(input())

dict_tm = eval(turing_machine)


for i in range(num_words): #for pra fazer a quantidade de palavras
    word = input()
    j=0
    verify_word(word, dict_tm)

    



