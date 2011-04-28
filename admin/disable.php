<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?>
<?php
	require_once '/home/silkwire/public_html/vulabdev/admin/phpESP.ini.php';
	require_once ($ESPCONFIG['include_path']."/lib/vulabdatalib.php");
    esp_init_adodb();
    $sql = "UPDATE $ESPCONFIG[user_table] SET `disabled` = 'Y' WHERE `username` = '$_REQUEST[username]'";
    $result = execute_sql($sql);
?>
The user <?php echo ($_REQUEST['username']); ?> has been set inactive in the database.