<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?><?php

require ESP_BASE.'admin/sanitize.php';


//Load All Projects for the direct access visitors
$surveys = get_surveys();

$ids = explode(',',$_GET[id]);

rm_surveys($ids);
?>
<h2><?php echo(_('Remove Surveys')); ?></h2>
<pre style="text-align:left;">
<?php
	while($survey = fetch_row($surveys))
	{
		$surveys->MoveNext();
		echo "<pre>";
		print_r($survey);
		echo "</pre>";
	}
?>
</pre>