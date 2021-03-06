#!/bin/bash
#------------------------------------------------------------------------------------------------
# All these commands were tested on my DB.
#
# Some must be used with utmost care!!!
#------------------------------------------------------------------------------------------------

# Working for influx DB
# ---------------------
# Creates the data base
#curl -i -X POST 'http://ds218plus.local:8086/query' --data-urlencode "q=CREATE DATABASE heatingdb"

# Delete data base
####curl -i -X POST 'http://ds218plus.local:8086/query' --data-urlencode "q=DROP DATABASE heatingdb"

# Creates the data base
#curl -i -X POST 'http://ds218plus.local:8086/query' --data-urlencode "q=CREATE DATABASE heatingdb"

#Posts successful
#curl -i -X POST 'http://ds218plus.local:8086/write?db=heatingdb' --data-binary 'cpu_load_short,host=server01,region=us-west value=0.65'
#curl -i -X POST 'http://ds218plus.local:8086/write?db=heatingdb' --data-binary 'cpu_load_short,host=server01,region=us-east value=0.35'

#Timed entry in ns
#curl -i -X POST 'http://ds218plus.local:8086/write?db=heatingdb' --data-binary 'cpu_load_short,host=server01,region=us-east value=0.6 1591275600000000000'


# Real data, in the format used for the heating data.
#curl -i -X POST 'http://ds218plus.local:8086/write?db=heatingdb' --data-binary 'heating_data,unit=degree Aussentemperatur=12.5'


# Shows all databases
curl -i -X POST 'http://ds218plus.local:8086/query' --data-urlencode "q=SHOW DATABASES"
