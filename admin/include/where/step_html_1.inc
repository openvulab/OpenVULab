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
if (!$project->details[start]) {
$checked['start'] = 'checked="checked"';
$disabled['start'] = 'disabled="disabled"';
}

if (!$project->details[end]) {
$checked['end'] = 'checked="checked"';
$disabled['end'] = 'disabled="disabled"';
}
?>
<div class="column">
<h1><?php echo(_('Project Details')); ?></h1><br />

	<label for="pname">Name<em>(required)</em>:</label>
	<input type="text" name="pname" id="pname" class="form_field" onchange="textChanged()" value="<?php 
	if ($project->details[name]){
		echo $project->details[name];
	}else{
		echo ($_POST[pname]);
	}
	?>"/>
<br /><br />
	<label for="pintro">Introduction:<br/><em>Give a brief overview what your study is all about</em></label>
	<textarea cols="20" rows="5" name="pintro" id="pintro"  class="form_field" onchange="textChanged()" ><?php 
	if ($project->details[intro]){
		echo $project->details[intro]; 
	}else{
		echo($_POST[pintro]);
	}?></textarea>
<br /><br />
<?php
/*<field>
	<label>Study Goal:<br/><em>What are the specifics of what your are trying to test or accomplish?<br/>ex. We are trying to test the usability of a function, </em></label>
	<textarea cols="20" rows="5" name="pgoal" id="pgoal"  class="form_field"/><?php echo $project->details[goal]; ?></textarea>
</field><br />
*/ ?>

	<label for="purl">URL to be Tested:</label>
	<input type="text" name="purl" id="purl"  class="form_field" value="<?php 
	if ($project->details[url]){
		echo $project->details[url]; 
	}else{
		echo ($_POST[purl]);
	}
	?>" onchange="textChanged()" />
<br /><br />
<label for="pthanks">Thank-you Message:</label><textarea cols="20" rows="5" name="pthanks" id="pthanks" onchange="textChanged()" ><?php
	if ($project->details[outro]){
		echo $project->details[outro]; 
	}else{
		echo ($_POST[pthanks]);
	}
	?></textarea>
<br /><br />
<input type="hidden" name="from" value="1" id="from" />
<input type="hidden" name="go" value="2" id="go" />
<input type="hidden" name="where" value="create" id="where" />
<div class="buttons"><input type="button" value="Cancel" onclick="window.location.href='manage.php?where=manage'"/><input type="submit" value="Save as Draft and Continue" /></div>
</div>