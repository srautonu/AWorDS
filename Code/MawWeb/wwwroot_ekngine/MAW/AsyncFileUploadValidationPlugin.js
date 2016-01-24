(function ($) {
    $.fn.Validate = function (options) {
        var defaults = {};
        var options = $.extend(defaults, options);
        return this.each(function () {
            if (typeof options.ValidFileExtensions == "undefined" || options.ValidFileExtensions == null) {
                options.ValidFileExtensions = [];
            }
            eval("OnStart('" + this.id + "', '" + options.MessageControlId + "', '" + options.ValidFileExtensions.join(",") + "')");
        });
    };
})(jQuery);

function OnStart(id, MessageControlId, ValidFileExtensions) {
    AjaxControlToolkit.AsyncFileUpload.prototype._onStart = function () {
        var valid = this.raiseUploadStarted(new AjaxControlToolkit.AsyncFileUploadEventArgs(this._inputFile.value, null, null, null));
        if (typeof valid == 'undefined') {
            valid = true;
        }
        if (valid && this._inputFile.id.indexOf(id) != -1) {
            valid = Validate(this._inputFile.value, MessageControlId, ValidFileExtensions.length > 0 ? ValidFileExtensions.split(",") : null);
            if (!valid) {
                this._innerTB.value = "";
                this._innerTB.style.backgroundColor = this._completeBackColor;
            }
        }
        return valid;
    }
}
function Validate(path, messageControlId, ValidFileExtensions) {
    $("#" + messageControlId).css("display", "none");
    var ext = path.substring(path.lastIndexOf(".") + 1, path.length).toLowerCase();
    var isValidFile = false;
    if (ValidFileExtensions != null) {
        for (var i = 0; i < ValidFileExtensions.length; i++) {
            if (ext == ValidFileExtensions[i]) {
                isValidFile = true;
                break;
            }
        }
    } else {
        isValidFile = true;
    }
    if (!isValidFile) {
        $("#" + messageControlId).css("display", "block");
    }
    return isValidFile;
}