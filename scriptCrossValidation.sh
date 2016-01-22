# Creamos copia desordenada de los datos del modelo.
cat ./invSim64/resources/input.csv | sort -R > ./invSim64/resources/temp.csv

# Obtenemos lista de clases: Comprar-SI, Comprar-NO.
clases=$(cat ./invSim64/resources/temp.csv | cut -d ',' -f9 | sort -u)

# Recorremos cada una de las lineas del fichero
for i in $clases
do
	# Ver clases.
	# echo $i
	grep $i ./invSim64/resources/temp.csv > /tmp/clase.txt
	# Contar elementos por clase.
	total=$(cat /tmp/clase.txt | wc -l)
	# Calcular número de elementos finales de cada clase por fichero.
	parcial=$((${total}/10))
	# echo $i $total $parcial
	# Dividir elementos en ficheros temporales
	split -l $parcial /tmp/clase.txt -d /tmp/cc
	# Concatenar a fichero.
	for p in 00 01 02 03 04 05 06 07 08 09
	do
		cat /tmp/cc$p | cut -d ',' -f1,2,3,4,5,6,7,8 | sort -r >> ./invSim64/resources/CrossValidation/$p
	done
done

# Trabajamos con las clases por separado.
rm ./invSim64/resources/temp.csv

#cat ./apl.csv | grep "-" > bufferGrep && wc -l bufferGrep
