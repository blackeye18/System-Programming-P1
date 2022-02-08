#!/bin/bash
#Test file creator for 1st assigment of SysPro
#sdi1800115 - Mavrommatis Panagiotis


function duplicate_id() {
	flag3=0
    for i in ${ids[@]}
	do
		if (($temp==$i))
		then
			flag3=1
			break
		fi
	done
	echo $flag3
}







get_name () {
	caps="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	normal="abcdefghijklmnopqrstuvwxyz"
	#megethos onomatos, elaxisto 3
	temp=$(( $RANDOM % 10 + 3 ))
	chooseletterindex=$(( $RANDOM % 26 ))
	#epilegoume kefalaio gia prwto gramma
	first_upper_letter=${caps:$chooseletterindex:1}
	#afairoume ena apo to megethos poy einai to kefalaio pou hdh vrhkame
	temp=$((temp-1))
	counter=0
	second_part=""
	#gia kathe gramma pou prepei na vrw
	while [ $counter -lt $temp ]
	do
		#dialegoume ena gramma
		chooseletterindex=$(( $RANDOM % 26 ))
		#kai to vazoume sto telos tou second part
		second_part=$second_part${normal:chooseletterindex:1}
		counter=$((counter+1))
	done
	#vazoume sthn arxh tou second part to kefalaio pou epileksame prin kai to "epistrefoume"
	returned_name=$first_upper_letter$second_part
	echo $returned_name
	
}


Country_virus_yesno_date (){
	#KSEKINAEI VIRUS
	temp=$(( $RANDOM % virus_counter ))
	virus=${virus_array[$temp]}
	echo -n " " >> inputfile
	echo -n $virus >> inputfile
	#TELOS VIRUS
	#KSEKINAEI YES/NO
	flag=$(( $RANDOM % 2 ))
	echo -n " " >> inputfile
	if (( $flag == 1 ))
	then
		#AN EXEI KANEI EMVOLIO VAZW HMEROMHNIA
		echo -n "${yes_or_no[$flag]}" >> inputfile
		temp=$(( $RANDOM % 30 + 1 ))
		final="$temp"
		final=$final"-"
		temp=$(( $RANDOM % 12 + 1 ))
		final=$final"$temp""-"
		temp=$(( $RANDOM % 21 ))
		temp=$((temp + 2000))
		final=$final"$temp"
		echo -n " " >> inputfile
		if ((i == $numoflines-1))
		then
			echo -n "$final" >> inputfile
		else 
			echo "$final" >> inputfile
		fi
	else
		#AN DEN EXEI KANEI EMVOLIO APLWS VAZW TO NO KAI TELOS
		if ((i == $numoflines-1))
		then
			echo -n "${yes_or_no[$flag]}" >> inputfile
		else 
			echo "${yes_or_no[$flag]}" >> inputfile
		fi
	fi


}

rm -f -- inputfile

if [ $# -ne 4 ]
then
	echo "Wrong number of arguents!"
	exit 1
fi

file_with_viruses=$1
file_with_countries=$2
numoflines=$3
duplicates=$4

if [ -f $file_with_viruses ]
then
	#virus_counter=1
	#while read line; do 
	#virus_counter=$((virus_counter+1))
	#done < $file_with_viruses
	readarray virus_array < $file_with_viruses
	virus_counter=${#virus_array[@]}
	echo "File with viruses: $file_with_viruses"
	echo "Viruses in file: $virus_counter"
else
	echo "Error! File $file_with_viruses does not exist"
fi
#echo ${virus_array[0]}
if [ -f $file_with_countries ]
then 
	#countries_counter=1
	#while read line; do 
	#countries_counter=$((countries_counter+1))
	#done < $file_with_countries
	readarray countries_array < $file_with_countries
	countries_counter=${#countries_array[@]}
	echo "File with countries: $file_with_countries"
	echo "Countries in file: $countries_counter"
else 
	echo "Error! File $file_with_countries does not exist"
fi
echo "Number of lines to create and export: $numoflines"
if (( $duplicates > 0 ))
then
	echo "Duplicates: Allowed"
else
	echo "Duplicates: Not Allowed"
fi
ids[0]=-1
yes_or_no[0]="NO"
yes_or_no[1]="YES"
flag2=0
for (( i=0; i<$numoflines; i++))
do
	#KSEKINAEI ID
	temp=$(( $RANDOM % 10000 ))
	while (( $(duplicate_id) ))
	do	
		#echo $temp
		temp=$(( $RANDOM % 10000 ))
		#echo $temp
	done
	ids[i]=$temp
	echo -n "$temp" >> inputfile
	#TELEIWNEI ID
	#KSEKINAEI NAME-SURNAME
	ret1=$(get_name)
	echo -n " " >> inputfile
	echo -n "$ret1" >> inputfile
	ret2=$(get_name)
	echo -n " " >> inputfile
	echo -n "$ret2" >> inputfile
	#TELEIWNEI NAME SURNAME
	#KSEKINAEI COUNTRIES
	temp=$(( $RANDOM % countries_counter ))
	country=${countries_array[$temp]}
	echo -n " " >> inputfile
	echo -n $country >> inputfile
	#TELOS COUNTRY
	#KSEKINAEI HLIKIA
	hlikia=$(( $RANDOM % 120 + 1 ))
	echo -n " " >> inputfile
	echo -n "$hlikia" >> inputfile
	#TELOS HLIKIA
	Country_virus_yesno_date
	#Se periptwsh pou epitrepode ta duplicates
	if (( $duplicates == 1))
	then
		chance=$(( $RANDOM % 10 + 1 ))
		if (( $chance == 1 )) || ((( $flag2 == 0) && ($i == $((numoflines-1)) )))
		#1 stis 10 pithanothtes, 10 ta 100
		then
			flag2=$((flag2+1))
			echo -n "${ids[$i]}" >> inputfile
			echo -n " " >> inputfile
			echo -n "$ret1" >> inputfile
			echo -n " " >> inputfile
			echo -n "$ret2" >> inputfile
			echo -n " " >> inputfile
			echo -n $country >> inputfile
			echo -n " " >> inputfile
			echo -n "$hlikia" >> inputfile
			Country_virus_yesno_date
			i=$((i+1))
		fi
	fi
done
echo "Finished exporting $numoflines line(s) to file inputfile with $flag2 duplicate(s)."

