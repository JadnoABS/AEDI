gcc -lm arvore.c -o arvore

testes=( "1" "2" "3" "4" "5" "13524" )

for i in "${testes[@]}"
do
  echo 'Teste '$i
  echo ''
  echo 'Resultado do programa:'
  ./arvore testes/"$i"_entrada.txt saida.txt
  cat saida.txt
  echo ''
  echo 'Resultado esperado:'
  cat testes/"$i"_saida.txt
  echo '---------------------------------'
done
