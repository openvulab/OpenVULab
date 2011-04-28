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

if ($where == 'manage') {

//error_reporting(E_ALL);
/* $Id: manage.inc,v 1.32 2007/12/03 13:08:13 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// For eGrad2000.com
// <jflemer@alum.rpi.edu>

$base =& $GLOBALS['ESPCONFIG']['ME'];
$bg = '';
$accessible = get_projects_by($_SESSION[acl]['userid'],2);

/* No longer needed
$projects = array();
foreach ($accessible as $perm) {
	unset($p);
	$p = new Project;
	$p->init($perm['projectid']);
	$myProjects[] = $p;
}*/

?>
<?php /*<h4>You have <?php echo  count($drafts_array); ?> draft projects</h4>*/ ?>
<?php /* <h4>You have <?php echo count($active_array); ?> active projects</h4>*/ ?>
<br />
<div id="container">
<div class="titlebar topped">
	<div class="left">
		<h1><?php echo(_('My Survey Projects')); ?></h1>
	</div>
</div>
<div class="column clear" style="width:90% !important;">
<div class="column box height3" style="width:90% !important;">
<h5>Survey Websites for Usability</h5>
<br />
<?php echo "<p>You've been invited to participate in the following usability studies!</p>" ?>
<br />
	<?php
		$fields = array('name');
		$options = array(	'titles'=>false,
							'link'=>'/public/project.php?id=<pid>',
							'link_attrib'=>'target="_blank"'
							);
		if (count($accessible) > 0) {
			echo display_projects_table($fields,$accessible,$options);
		} else {
		
		echo "<em>You don't have any Survey Projects Yet</em><br /><br /><br /><br /><br /><br /><br />";
		}
	?>
</div>
</div>
<?php /*</div>
</div><!-- col_left -->
<div id="col_right" class="column">
</div>*/ ?>


<?php } ?>
</div>