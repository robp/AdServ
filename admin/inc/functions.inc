<?php
  function format_numbers ($val) {
    $temp = strrev($val);

    for ($i = 0; $i < strlen($temp); $i++) {
      if ($i && ($i % 3) == 0) $temp2 .= ",";
      $temp2 .= $temp[$i];
    }

    return strrev($temp2);
  }

  // Check to see if a value is in the specified
  // database table. Return 0 if not, 1 if so.
  function db_item_exists ($label, $value, $table, $sock) {
    $query = "SELECT $label FROM $table
              WHERE $label = $value";

    if (!$sql_result = mysql_query($query, $sock)) {
      echo mysql_error();
      html_exit();
    }
     
    if (!mysql_num_rows($sql_result))
      return 0;
    else   
      return mysql_num_rows($sql_result);
  }        

  // Connect to the SQL server and select the database
  function db_connect () {
    if (!$sock = mysql_connect(DATABASE_HOST,DATABASE_USER,DATABASE_PASSWD)) {
      echo mysql_error();
      exit();          
    }
    if (!mysql_select_db(DATABASE_NAME, $sock)) {
      echo mysql_error();
      exit();          
    }

    return $sock;
  }

  // Get a username by its id
  function get_username_by_id ($table, $id, $sock) {
    $query = "SELECT username FROM $table
              WHERE id = " . $id;

    if (!$sql_result = mysql_query($query, $sock)) {
      echo mysql_error();
      html_exit();
    }

    if (mysql_num_rows($sql_result) == 1) {
      $sql_result_row = mysql_fetch_row($sql_result);
      return stripslashes($sql_result_row[0]);
    }
    else
      return -1;
  }

  // Get the total number of impressions served by a location, 
  // counting active and inactive ads
  function get_location_imps ($id, $sock) {
    $query = "SELECT SUM(imp_used) FROM ads
              WHERE location_id = " . $id;

    if (!$sql_result = mysql_query($query, $sock)) {
      echo mysql_error();
      html_exit();
    }

    $sql_result_row = mysql_fetch_row($sql_result);

    if ($sql_result_row[0] > 0)
      return $sql_result_row[0];
    else
      return 0;
  }

  function list_hosts_select($id, $sock) {
    $query = "SELECT id,username FROM hosts";
    
    if (!$sql_result = mysql_query($query, $sock)) {
      echo mysql_error();
      html_exit();
    }

    $num_rows = mysql_num_rows($sql_result);

    for ($a = 0; $a < $num_rows; $a++) {
      $sql_result_row = mysql_fetch_row($sql_result);
      $result .= "<option value=\"" . $sql_result_row[0] . "\"" . ($sql_result_row[0] == $id ? " selected" : "") . ">" . stripslashes($sql_result_row[1]);
    }

    echo $result;
  }

  function list_advertisers_select($id, $sock) {
    $query = "SELECT id,username FROM advertisers";
    
    if (!$sql_result = mysql_query($query, $sock)) {
      echo mysql_error();
      html_exit();
    }

    $num_rows = mysql_num_rows($sql_result);

    for ($a = 0; $a < $num_rows; $a++) {
      $sql_result_row = mysql_fetch_row($sql_result);
      $result .= "<option value=\"" . $sql_result_row[0] . "\"" . ($sql_result_row[0] == $id ? " selected" : "") . ">" . stripslashes($sql_result_row[1]);
    }

    echo $result;
  }
?>
