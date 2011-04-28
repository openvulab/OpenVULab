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

//error_reporting(E_ALL);
/* $Id: manage.inc,v 1.32 2007/12/03 13:08:13 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// For eGrad2000.com
// <jflemer@alum.rpi.edu>

$base =& $GLOBALS['ESPCONFIG']['ME'];
$bg = '';
if (!$_GET[type]) { $_GET[type] = 'draft'; }
if ($_GET[type] == 'draft') { 
	$projects_array = get_projects_by($_SESSION[acl]['userid'],1);
	$statusid = 1;
	$fields = array('name','url', 'createstamp');
}
elseif ($_GET[type] == 'active') {
	$projects_array = get_projects_by($_SESSION[acl]['userid'],2);
	$fields = array('name','url','activestamp');
	$statusid = 2;
}
elseif ($_GET[type] == 'completed') {
	$projects_array = get_projects_by($_SESSION[acl]['userid'],3);
	$fields = array('name','url','completestamp');
	$statusid = 3;
}
?>
<div  class="project_container">
    <br/>
<div class="titlebar">
	<div class="left">
		<h1><?php echo(_('View My '.ucwords($_GET[type]).' Projects')); ?></h1>
	</div>
	<div class="right">
		View Project Type: <a href="?where=viewall&amp;type=draft">Drafts</a> | <a href="?where=viewall&amp;type=active">Active</a> | <a href="?where=viewall&amp;type=completed">Completed</a>
	</div>
</div>
<div class="clear"></div>
<div class="padded">
	<?php
		$options = array('titles'=>true,'action_set'=>$_GET[type],'status'=>$statusid);
		if (count($projects_array) > 0) {
			echo display_projects_table($fields,array_reverse($projects_array),$options);
		} else {
		
		echo "<em>You don't have any $_GET[type] projects yet</em>";
		}
	?>
</div>
</div>
