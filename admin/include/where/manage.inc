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
	//$drafts_array = filter_projects_bystatus(get_projects_byowner($_SESSION[acl]['userid']),1,'==');
	//$active_array = filter_projects_bystatus(get_projects_byowner($_SESSION[acl]['userid']),2,'==');
	//$complete_array = filter_projects_bystatus(get_projects_byowner($_SESSION[acl]['userid']),6,'==');
	
	
	$drafts_array = get_projects_by($_SESSION['acl']['userid'],1,'editstamp DESC');
	$active_array = get_projects_by($_SESSION['acl']['userid'],2);
	$complete_array = get_projects_by($_SESSION['acl']['userid'],3);
	
	?>
	<?php /*<h4>You have <?php echo  count($drafts_array); ?> draft projects</h4>*/ ?>
	<?php /* <h4>You have <?php echo count($active_array); ?> active projects</h4>*/ ?>
<div>
	<br />
        

	<div id="container">
	<?php if ($_GET['success'] == 'deletedproject') {
		echo "<div id=\"goods\">You have successfully deleted the project!</div>";
		echo '<script type="text/javascript">
				$(document).ready(function() {
					$("#goods").animate({opacity: 1.0}, 2500).fadeOut("slow")
				});
			</script>
		';
}
?>
<?php if ($_GET['success'] == 'activatedproject') {
	echo "<div id=\"goods\">You have successfully <strong>activated</strong> the project!</div>";
	echo '<script type="text/javascript">
			$(document).ready(function() {
				$("#goods").animate({opacity: 1.0}, 2500).fadeOut("slow")
			});
		</script>
	';
}
?>
<?php if ($_GET['success'] == 'deactivatedproject') {
	echo "<div id=\"goods\">You have successfully <strong>deactivated</strong> the project!</div>";
	echo '<script type="text/javascript">
			$(document).ready(function() {
				$("#goods").animate({opacity: 1.0}, 2500).fadeOut("slow")
			});
		</script>
	';
}
?>
<div class="titlebar">
	<div class="left">
		<h1><?php echo(_('My Projects')); ?></h1>
	</div>
	<div class="right">
	<h1>
		<a href="?where=create" style="text-decoration:none;"><img src="../images/add.png" class="icon" alt="Create a new Project"/>Create a New Project</a>
	</h1>
	</div>
</div>
<?php /*<div id="col_left" class="column">*/ ?>
<div class="clear"></div>
<div class="column_home box width3 height3">
<h2 style="text-align:left;"><?php echo(_('Draft(s)')); ?></h2>
<?php echo"<h5>Projects I'm working on</h5><br />" ?>
	<?php
		$fields = array('name');
		$options = array('titles'=>false,'status'=>'draft','sort'=>'editstamp');
		if (count($drafts_array) > 0) {
			echo display_projects_table($fields,$drafts_array,$options);
			echo "<h5><a href='?where=viewall&amp;type=draft' class='right'>View All Draft Projects</a></h5>";
		} else {
		
		echo "<em>You don't have any draft projects yet</em><br /><br /><br /><br /><br /><br /><br />";
		}
	?>
</div>
<div class="column_home box width3 height3">
	<h2><?php echo(_('Active')); ?></h2>
	<h5>Projects gathering data</h5><br />
	<?php
		$fields = array('name');
		$options = array('titles'=>false,'status'=>'active');
		if (count($active_array) > 0) {
			echo display_projects_table($fields,$active_array,$options);
			echo "<h5><a href='?where=viewall&amp;type=active' class='right'>View All Active Projects</a></h5>";
		} else {
				echo "<em>You don't have any active projects yet</em><br /><br /><br /><br /><br /><br /><br/>";
		}
	?>
</div>

<div class="column_home box width3 height3">
	<h2><?php echo(_('Completed')); ?></h2>
	<h5>Projects finished collecting data</h5><br />
	<?php
		$fields = array('name');
		$options = array('titles'=>false,'status'=>'complete','link'=>'?where=viewcompleted&amp;pid=<pid>');
		if (count($complete_array) > 0) {
			echo display_projects_table($fields,$complete_array,$options);
			echo "<h5><a href='?where=viewall&amp;type=completed' class='right'>View All Completed Projects</a></h5>";
		} else {
		
		echo "<em>You don't have any closed projects yet</em><br /><br /><br /><br /><br /><br /><br />";
		}
	?>
</div>
<div class="clear"></div>
<?php 
/* 
######
## Taken out until Implemented
######
<div class="titlebar topped">
	<div class="left">
		<h1><?php echo(_('My Survey Templates')); ?></h1>
	</div>
	
	<div class="right">
	<h3>
		<img src="../images/add.png" class="icon"/><a href="?where=create">Create Survey Template</a>
	</h3>
	</div>
</div>
<div class="column clear">
<div class="column_home box width3 height3">
<h5>Generic Templates to be Reused</h5><br />
	<?php
		$fields = array('name');
		$options = array('titles'=>false,'status'=>'draft','sort'=>'editstamp');
		if (count($drafts_array) > 0) {
			echo display_projects_table($fields,$drafts_array,$options);
			echo "<h5><a href='?where=viewall&type=draft' class='right'>View All Draft Projects</a></h5>";
		} else {
		
		echo "<em>You don't have any draft projects yet</em><br /><br /><br /><br /><br /><br /><br />";
		}
	?>
</div>*/ ?>
</div>
</div>
<?php /*</div>
</div><!-- col_left -->
<div id="col_right" class="column">
</div>*/ ?>


<?php } ?>
