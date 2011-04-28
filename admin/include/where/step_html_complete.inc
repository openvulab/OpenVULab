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
	$("a[href='#complete']").click(function() {
		$("input[name='complete']").attr('value','true');
		$("a[href='#complete'] span").attr('class','green');
		$("a[href='#later'] span").attr('class','grey');
		$('#complete_continue').fadeIn();
	});
	$("a[href='#later']").click(function() {
		$("input[name='complete']").attr('value','false');
		$("a[href='#complete'] span").attr('class','grey');
		$("a[href='#later'] span").attr('class','green');
		$('#complete_continue').fadeOut();
	});
});
</script>
<div class="column" style="margin-left:50px;">
<h1 style="text-align:center !important;">complete "<?php echo $project->details[name]; ?>"</h1>
<div class="note margined">
	<div>Note: You will be setting this project to "complete" which will change the start date to <strong>today</strong></div>
	<div>This means your project will <span>now be available to the public</span> and your project will be able to capture data</div>
</div>
<div style="padding:20px 0px 0px 50px;text-align:center;" class="left">
<h2><a href="#complete"><span class="grey">complete Project</span></a></h2>
<h2><a href="#later"><span class="green">complete Later</span></a></h2>
</div>
<div class="left" id="complete_continue" style="text-align:left !important;padding:10px;display:none;">
	<input type="submit" value="Click Here to complete Project!"/><br /><br/>
	<div class="note">
		Note: This cannot be undone, and you will no longer be able to change project fields. <br />
		<strong>You will only be able to manage testers</strong>
	</div>
</div>
<input type="hidden" name="complete" value=""/>
<input type="hidden" name="from" value="4" id="from" />
<input type="hidden" name="go" value="5" id="go" />
<input type="hidden" name="where" value="create" id="where" />
</div>