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
/* $Id: finish.inc,v 1.15 2005/08/01 16:12:54 greggmc Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// For eGrad2000.com
// <jflemer@alum.rpi.edu>

	$_SESSION['new_survey'] = false;
	$survey_name = "";
    $sql = "SELECT name FROM ".$GLOBALS['ESPCONFIG']['survey_table']." WHERE id = ". $_SESSION['survey_id'];
    if ($result = execute_sql($sql)) {
	    if (record_count($result) > 0)
		    $survey_name = $result->fields[0];
		db_close($result);
	}

?>
<script type="text/javascript">
function validate() {
    return true;
}
</script>
<br />
<strong><?php echo(_('Survey Design Completed')); ?></strong>

	<p><?php echo(_('You have completed this survey design. Click any button 1-4 <strong>above</strong> to continue')); ?></p>



<?php // echo("<a href=\"". $GLOBALS['ESPCONFIG']['ME'] ."?where=manage\">" . _('Go back to Management Interface') . "</a>\n"); 
?>