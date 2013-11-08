function DropDown(el) {
                this.dd = el;
                this.initEvents();
            }

DropDown.prototype = {
    initEvents : function() {
        var obj = this;

        obj.dd.on('click', function(event){
            $(this).toggleClass('active');
            event.stopPropagation();
        });
    }
}

$(function() {

    var dd = new DropDown( $('#dd') );

    $(document).click(function() {
        // all dropdowns
        $('.wrapper-dropdown').removeClass('active');
    });

});
