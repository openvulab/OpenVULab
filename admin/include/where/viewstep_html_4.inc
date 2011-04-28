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
<script type="text/javascript">
$(document).ready(function() {
	$("a[href='#activate']").click(function() {
		$("input[name='activate']").attr('value','true');
		$("a[href='#activate'] span").attr('class','green');
		$("a[href='#later'] span").attr('class','grey');
		$('#activate_continue').fadeIn();
	});
	$("a[href='#later']").click(function() {
		$("input[name='activate']").attr('value','false');
		$("a[href='#activate'] span").attr('class','grey');
		$("a[href='#later'] span").attr('class','green');
		$('#activate_continue').fadeOut();
	});
});
</script>
<div class="column" style="margin-left:50px;">
<h1 style="text-align:center !important;">Activate "<?php echo $project->details[name]; ?>"</h1>
<div class="note margined">
	<div>Note: You will be setting this project to "active" which will change the start date to <strong>today</strong></div>
	<div>This means your project will <span>now be available to the public</span> and your project will be able to capture data</div>
</div>
<div style="padding:20px 0px 0px 50px;text-align:center;" class="left">
<h2><a href="#activate"><span class="grey">Activate Project</span></a></h2>
<h2><a href="#later"><span class="green">Activate Later</span></a></h2>
</div>
<div class="left" id="activate_continue" style="text-align:left !important;padding:10px;display:none;">
	<input type="submit" value="Click Here to Activate Project!"/><br /><br/>
	<div class="note">
		Note: This cannot be undone, and you will no longer be able to change project fields. <br />
		<strong>You will only be able to manage testers</strong>
	</div>
</div>
<input type="hidden" name="activate" value=""/>
<input type="hidden" name="from" value="4" id="from" />
<input type="hidden" name="go" value="5" id="go" />
<input type="hidden" name="where" value="view" id="where" />
</div>