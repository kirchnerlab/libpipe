/**
 * @author David Sichau
 */
$(function() {

	var filterId, paramId, allFields;

	//updates the input files
	function update() {
		filterId = $('#del_param #filter_selector');
		paramId = $("#del_param #parameter_selector");
		allFields = $([]).add(filterId).add(paramId);
	}

	//dialog box for adding deleting parameter
	$("#del_param").dialog({
		autoOpen : false,
		width: 'auto',
		modal : true,
		buttons : {

			"Delete Parameters" : function() {
				var bValid = true;
				allFields.removeClass("ui-state-error");
				if(filterId.val()==-1) {
					bValid = false;
					filterId.addClass("ui-state-error");
				}
				if(paramId.val()==-1) {
					bValid = false;
					paramId.addClass("ui-state-error");
				}
		

				if(bValid) {
					completeFilter.params.delParams(filterId.val(), paramId.val());
					$(this).dialog("close");
				}
			},
			Cancel : function() {
				$(this).dialog("close");
			}
		},
		close : function() {
			allFields.val("").removeClass("ui-state-error");
			html_ = completeFilter.params.printJSON("showParams")
			$('#showParams').html(html_);
		}
	});

	// generate the html with the filter selector
	function generateHTML() {
		var html = '<p>';
		html += '	Select the parameter:';
		html += '</p>';
		html += '<p><label>filterIdentifier:</label> <select name="filter_selector" id="filter_selector">';
		html += '<option value="-1">choose your filter</option>'
		$.each(completeFilter.params.getJSON(), function() {
			$.each(this, function(id) {
				$.each(this, function(index, value) {
					if(!$.isArray(value)) {
						html += '	<option value="' + id + '">' + value + '</option>'
					}
				});
			});
		});
		html += '</select></p><p id="param_chooser"></p>';
		return html;
	}

	//checks if selector is changed
	$('#filter_selector').live('change', function() {
		var html = '<label>paramIdentifier:</label> <select name="parameter_selector" id="parameter_selector"><option value="-1">choose your parameter</option>';
		$.each(completeFilter.params.getJSON(), function() {
			$.each(this, function(id) {
				if(id == $('#filter_selector').val()) {
					$.each(this, function(index, value) {
						if($.isArray(value)) {
							$.each(this, function(id2) {
								$.each(this, function(index2, value2) {
									if(index2 == 'paramIdentifier') {
										html += '	<option value="' + id2 + '">' + value2 + '</option>'
									}
								});
							});
						}
					});
				}

			});
		});
		html+= '</select>'
		$('#del_param #param_chooser').html(html);
		update();
		
	});
	// open dialog with the new parameter file
	$('#showParams #delParam').live('click', function() {
		var html_ = generateHTML();
		$('#del_param').html(html_);
		update();

		$(function() {
			$("#del_param").dialog("open");
		});
	});
});
