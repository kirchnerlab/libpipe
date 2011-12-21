/**
 * @author David Sichau
 */
$(function() {

	var filterId, paramId, allFields;

	//updates the input files
	function update() {
		pipelineId = $('#del_pipeline #pipeline_selector');
		allFields = $([]).add(pipelineId);
	}

	//dialog box for adding deleting parameter
	$("#del_pipeline").dialog({
		autoOpen : false,
		width: 'auto',
		modal : true,
		buttons : {

			"Delete Parameters" : function() {
				var bValid = true;
				allFields.removeClass("ui-state-error");
				if(pipelineId.val()==-1) {
					bValid = false;
					pipelineId.addClass("ui-state-error");
				}
				
				if(bValid) {
					completeFilter.pipeline.delPipeline(pipelineId.val());
					$(this).dialog("close");
				}
			},
			Cancel : function() {
				$(this).dialog("close");
			}
		},
		close : function() {
			allFields.val("").removeClass("ui-state-error");
			html_ = completeFilter.pipeline.printJSON("showPipeline")
			$('#showPipeline').html(html_);
		}
	});

	// generate the html with the filter selector
	function generateHTML() {
		var html = '<p>';
		html += '	Select the parameter:';
		html += '</p>';
		html += '<p><label>filterIdentifier: </label><select name="pipeline_selector" id="pipeline_selector">';
		html += '<option value="-1">choose your pipeline object</option>'
		$.each(completeFilter.pipeline.getJSON(), function() {
			$.each(this, function(id, temp) {
				$.each(this, function(index, value) {
					if(index == "filterName") {
						html += '	<option value="' + id + '">' + value +'; requestRank:'+ temp.requestRank +'</option>'
					}
				});
			});
		});
		html += '</select></p><p id="param_chooser"></p>';
		return html;
	}

	
	// open dialog with the new parameter file
	$('#showPipeline #delPipeline').live('click', function() {
		var html_ = generateHTML();
		$('#del_pipeline').html(html_);
		update();

		$(function() {
			$("#del_pipeline").dialog("open");
		});
	});
});
