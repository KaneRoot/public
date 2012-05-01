#!/bin/bash


for i in $(ls "./plsql")
do
	echo "@plsql/${i}" >> pl.sql
done
