
def verify_word(word, dict_tm):
    tape = word + "bbbbbbbbbbbb"
    tape_list=[]
    
    for i in range(len(tape)):
        tape_list.append(tape[i])
    
    
    begin = dict_tm['inicial']
    accept = dict_tm['aceita']
    reject = dict_tm['rejeita']
    delta = dict_tm['delta']
    
    is_moving = True
    current_state = begin
    delta_size = len(delta)
    i=0
    
    
    while is_moving: #while pra percorrer a palavra
        
        for j in range(delta_size):
            
            if current_state == delta[j][0] and tape_list[i]== str(delta[j][2]):
                
                current_state = delta[j][1]
                
                if str(delta[j][3]) != 'b':
                    tape_list[i] = str(delta[j][3])
                    
                
                if(delta[j][4] == 'D'):
                    i +=1
                    break
                elif delta[j][4] == 'E':
                    i -=1
                    break
                elif delta[j][4] == 'P':
                    is_moving = False
                    break
                
    final_world=''
    k=0
    while tape_list[k] != 'b':
        final_world += tape_list[k]
        k+=1
    if current_state== accept:
        print(final_world, "ACEITA") 
    elif current_state == reject:
        print(final_world, "REJEITA")         
            
  
        
        

turing_machine = input()
num_words = int(input())

dict_tm = eval(turing_machine)


for i in range(num_words): #for pra fazer a quantidade de palavras
    word = input()
    
    j=0
    verify_word(word, dict_tm)

    



