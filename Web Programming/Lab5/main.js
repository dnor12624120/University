var orderAttr = 'data-order';

function switchButtonOrder(button1, button2) {
  var tmp = button1.attr(orderAttr);
  button1.attr(orderAttr, button2.attr(orderAttr));
  button2.attr(orderAttr, tmp);
}

function setButtonTop(button, top_value) {
  button.css({ top: top_value + 'px' });
}

$(function() {
  $('.button').mousedown(function(e) {
    var button = $(this);
    var button_id = button.attr('id');
    var parent_height = button.parent().innerHeight();
    var top = parseInt(button.css('top'));
    var original_ypos = button.position().top; //original ypos
    var drag_min_ypos = 0 - original_ypos;
    var drag_max_ypos = parent_height - original_ypos - button.outerHeight();
    var drag_start_ypos = e.clientY;
    var my_ypos = original_ypos;
    //Set current order for all
    $('.button').each(function(i) {
       $(this).attr('data-order', (i + 1));
    });
    var prev_button = button.prev('.button');
    var next_button = button.next('.button');
    var prev_button_ypos = prev_button.length > 0 ? prev_button.position().top : '';
    var next_button_ypos = next_button.length > 0 ? next_button.position().top : '';
    $(window).on('mousemove', function(e) {
      //Move and constrain
      button.addClass('drag');
      var direction = my_ypos > button.position().top ? 'up' : 'down';
      var new_top = top + e.clientY - drag_start_ypos;
      my_ypos = button.position().top;
      setButtonTop(button, new_top);
      button.css({
        top: new_top+'px'
      });
      if(new_top < drag_min_ypos) {
        button.css({
          top: drag_min_ypos + 'px'
        });
      }
      if(new_top > drag_max_ypos) {
        button.css({
          top: drag_max_ypos + 'px'
        });
      }
      //Check position over others
      if(direction == 'down' && next_button_ypos != '') {
        if(my_ypos > next_button_ypos) { //crossed next button
          next_button.css({
            top: parseInt(next_button.css('top')) - next_button.outerHeight(true) + 'px'
          }); //up once
          switchButtonOrder(next_button, button);
          prev_button = next_button;
          next_button = next_button.nextAll('.button:not(.drag)').first();
          prev_button_ypos = prev_button.length > 0 ? prev_button.position().top : '';
          next_button_ypos = next_button.length > 0 ? next_button.position().top : '';
        }
      }
      else if(direction == 'up' && prev_button_ypos != '') {
        if(my_ypos < prev_button_ypos) { //crossed prev button
          prev_button.css({
            top: parseInt(prev_button.css('top') +prev_button.outerHeight(true)) + 'px'
          }); //down once
          switchButtonOrder(prev_button, button);
          next_button = prev_button;
          prev_button = prev_button.prevAll('.button:not(.drag)').first();
          prev_button_ypos = prev_button.length > 0 ? prev_button.position().top : '';
          next_button_ypos = next_button.length > 0 ? next_button.position().top : '';
        }
      }
    });
    $(window).on('mouseup', function(e) {
      $('.button').removeClass('drag');
      $(window).off('mouseup mousemove');
      //Reorder and reposition all
      $('.button').each(function() {
        var this_order = parseInt($(this).attr('data-order'));
        var prev_order = $(this).siblings('.button[data-order="' + (this_order - 1) + '"]');
        if(prev_order.length > 0) {
          $(this).insertAfter(prev_order);
        }
      });
      $('.button').css('top','0');
      $('.button').removeAttr('data-order'); //reset
    });
  });
});
