function other_check(name)
{
  other = name.split("_");
  var f = document.phpesp;
  for (var i=0; i<=f.elements.length; i++) {
    if (f.elements[i].value == "other_"+other[1]) {
      f.elements[i].checked=true;
      break;
    }
  }
}
function validate() {
    return true;
}
