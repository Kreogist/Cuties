function ShowDialog(id){
    HideDialogs();
    document.getElementById(id).setAttribute("class","dialog active");

}
function HideDialogs(){
    var diaList = ["dialog-windows","dialog-mac","dialog-linux"];
    for (var i = 0,len = diaList.length;i<len;i++){
        document.getElementById(diaList[i]).setAttribute("class","dialog");
    }
}