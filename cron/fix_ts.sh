#!/bin/bash
cd $1
arr=(*.jpg);
len=${#arr[*]};
i=0;
while [ $i -lt $(($len -1))  ];
do
	a=`echo ${arr[${i}]} | cut -f1 -d'.'`
	b=`echo ${arr[${i}+1]} | cut -f1 -d'.'`

	difference=$(($b - $a))

	pads=$(($difference / 100))
	j=0
	while [ $j -lt $pads ];
	do
		fname=$(($a + 100 * $j))
		cp $a.jpg  $fname.jpg
		((j++))
	done
	((i++))
done
