<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/

class DB {
	
	function __construct($databaseKey = 'main'){
		global $db;
		$this->dbkey = $databaseKey;
		$this->db = $db[$this->dbkey];
	}
	function setTable($tablename){
		$this->table = $tablename;
		$this->fields = getFields();
	}
	function getFields(){
		$fields = mysql_list_fields($this->db['dbname'], $this->table, $this->db['link']);
		$columns = mysql_num_fields($fields);
		for ($i = 0; $i < $columns; $i++) {
		   	$fields[] =  mysql_field_name($fields, $i) . "\n";
		}
		return $fields;
	}
	function setKey($key){
		$this->key = $key;
	}
	function update($data,$where,$options=array()){
		 $updateQuery .= "UPDATE ".$this->table." SET ";
        
        foreach ($fields as $field) {
          # update each field
          $updateQuery .= "`". $field ."` = '". $data[$field] ."', ";
        }
        
        # remove the last comma
        $updateQuery = substr($updateQuery, 0, -2);
        
        # finish the query
        $updateQuery .= " WHERE `".$this->key."` = '". $where ."'";
		
		# execute the query
        mysql_query($updateQuery, $this->db['link']) or die(mysql_error());
		return true;
	}
	
	function delete($where){
		if (!is_array($where)){
			$deleteQuery = 'DELETE FROM '.$this->table.' WHERE '.$this->key.'='."'$where'";
		}
		mysql_query($deleteQuery,$this->db['link']) or die(mysql_error());
		return true;
	}
	function add($values,$options=array()){
		
	}
}
function dbConnect($key){
  # include database information
  global $db;
  
  # create a connection to the database
  $link = mysql_connect($db[$key]['host'], $db[$key]['user'], $db[$key]['pass'], true) or die("$key Database Connection Failed!");
  mysql_select_db($db[$key]['dbname'], $link) or die($db[$key][dbname] . " Database Does Not Exist!");
  
  return $link;
}
?>