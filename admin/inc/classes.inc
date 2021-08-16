<?php
  class Location {
    var $id;
    var $host_id;
    var $title;
    var $width;
    var $height;
    var $img_loc;
    var $filters;
    var $freq_cnt;
    var $next_ad;
    var $mail_threshold;
    var $opened;
    var $closed;
    var $active;


    // Lets polymorph the crap out of this constructor.  Not really
    // built into PHP, but we'll fudge it. Why didn't I think of this
    // before??

    function Location ($sql_result_row, $id, $sock) {
      // If a second argument is passed, then we know we're trying to
      // populate this object by getting the data from the database,
      // based on the id.  We'll just put the data into the
      // sql_result_row variable, so that the next paragraph picks it up.
      if ($id) {
        $query = "SELECT * FROM locations
                  WHERE id = " . $id;

        if (!$sql_result = mysql_query($query, $sock)) {
          echo mysql_error();
          html_exit();
        }

        if (mysql_num_rows($sql_result) == 1) {
          $sql_result_row = mysql_fetch_row($sql_result);
        }
      }

      // Either 1) the sql_result_row was passed to us as a parameter,
      // or 2) the variable was set in the above paragraph. Either way,
      // populate this object's variables.
      if ($sql_result_row) {
        $this->id = $sql_result_row[0];
        $this->host_id = $sql_result_row[1];
        $this->title = stripslashes($sql_result_row[2]);
        $this->width = $sql_result_row[3];
        $this->height = $sql_result_row[4];
        $this->img_loc = stripslashes($sql_result_row[5]);
        $this->filters = $sql_result_row[6];
        $this->freq_cnt = $sql_result_row[7];
        $this->next_ad = $sql_result_row[8];
        $this->mail_threshold = $sql_result_row[9];
        $this->opened = $sql_result_row[10];
        $this->closed = $sql_result_row[11];
        $this->active = $sql_result_row[12];
      }
      // No parameters, so just return, creating an empty object.
      else
        return;
    }

    function insert ($sock) {
      $query = "INSERT INTO locations
                VALUES (NULL, $this->host_id, 
                        '" . addslashes($this->title) . "',
                        $this->width, $this->height,
                        '" . addslashes($this->img_loc) . "',
                        $this->filters, $this->freq_cnt,
                        $this->next_ad, $this->mail_threshold,
                        $this->opened, $this->closed, $this->active)";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }

      $this->id = mysql_insert_id();
    }

    function update ($sock) {
      $query = "UPDATE locations
                SET host_id = $this->host_id, 
                    title = '" . addslashes($this->title) . "',
                    width = $this->width, 
                    height = $this->height, 
                    img_loc = '" . addslashes($this->img_loc) . "',
                    filters = $this->filters, 
                    freq_cnt = $this->freq_cnt, 
                    next_ad = $this->next_ad,
                    mail_threshold = $this->mail_threshold,
                    opened = $this->opened, 
                    closed = $this->closed, 
                    active = $this->active
                WHERE id = $this->id";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }
    }
  }

  class Ad {
    var $id;
    var $location_id;
    var $advertiser_id;
    var $filename;
    var $alttext;
    var $link_url;
    var $imp_purchased;
    var $imp_used;
    var $frequency;
    var $clickthroughs;
    var $opened;
    var $closed;
    var $active;

    function Ad ($sql_result_row, $id, $sock) {
      // If a second argument is passed, then we know we're trying to
      // populate this object by getting the data from the database,
      // based on the id.  We'll just put the data into the
      // sql_result_row variable, so that the next paragraph picks it up.
      if ($id) {
        $query = "SELECT * FROM ads
                  WHERE id = " . $id;

        if (!$sql_result = mysql_query($query, $sock)) {
          echo mysql_error();
          html_exit();
        }

        if (mysql_num_rows($sql_result) == 1) {
          $sql_result_row = mysql_fetch_row($sql_result);
        }
      }

      // Either 1) the sql_result_row was passed to us as a parameter,
      // or 2) the variable was set in the above paragraph. Either way,
      // populate this object's variables.
      if ($sql_result_row) {
        $this->id = $sql_result_row[0];
        $this->location_id = $sql_result_row[1];
        $this->advertiser_id = $sql_result_row[2];
        $this->filename = stripslashes($sql_result_row[3]);
        $this->alttext = stripslashes($sql_result_row[4]);
        $this->link_url = urldecode($sql_result_row[5]);
        $this->imp_purchased = $sql_result_row[6];
        $this->imp_used = $sql_result_row[7];
        $this->frequency = $sql_result_row[8];
        $this->clickthroughs = $sql_result_row[9];
        $this->opened = $sql_result_row[10];
        $this->closed = $sql_result_row[11];
        $this->active = $sql_result_row[12];
      }
      // No parameters, so just return, creating an empty object.
      else
        return;
    }

    function insert ($sock) {
      $query = "INSERT INTO ads
                VALUES (NULL, $this->location_id, $this->advertiser_id,
                        '" . addslashes($this->filename) . "', 
                        '" . addslashes($this->alttext) . "',
                        '" . urlencode($this->link_url) . "',
                        $this->imp_purchased, $this->imp_used,
                        $this->frequency, $this->clickthroughs, 
                        $this->opened, $this->closed, $this->active)";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }

      $this->id = mysql_insert_id();
    }

    function update ($sock) {
      $query = "UPDATE ads
                SET location_id = $this->location_id,
                    advertiser_id = $this->advertiser_id,
                    filename = '" . addslashes($this->filename) . "',
                    alttext = '" . addslashes($this->alttext) . "',
                    link_url = '" . urlencode($this->link_url) . "',
                    imp_purchased = $this->imp_purchased,
                    imp_used = $this->imp_used,
                    frequency = $this->frequency,
                    clickthroughs = $this->clickthroughs,
                    opened = $this->opened,
                    closed = $this->closed,
                    active = $this->active
                WHERE id = $this->id";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }
    }
  }

  class Filter {
    var $id;
    var $location_id;
    var $filter;

    function Filter ($sql_result_row, $id, $sock) {
      // If a second argument is passed, then we know we're trying to
      // populate this object by getting the data from the database,
      // based on the id.  We'll just put the data into the
      // sql_result_row variable, so that the next paragraph picks it up.
      if ($id) {
        $query = "SELECT * FROM filters
                  WHERE id = " . $id;

        if (!$sql_result = mysql_query($query, $sock)) {
          echo mysql_error();
          html_exit();
        }

        if (mysql_num_rows($sql_result) == 1) {
          $sql_result_row = mysql_fetch_row($sql_result);
        }
      }

      // Either 1) the sql_result_row was passed to us as a parameter,
      // or 2) the variable was set in the above paragraph. Either way,
      // populate this object's variables.
      if ($sql_result_row) {
        $this->id = $sql_result_row[0];
        $this->location_id = $sql_result_row[1];
        $this->filter = stripslashes($sql_result_row[2]);
      }
      // No parameters, so just return, creating an empty object.
      else
        return;
    }

    function insert ($sock) {
      $query = "INSERT INTO filters
                VALUES (NULL, $this->location_id,
                        '" . addslashes($this->filter) . "')";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }

      $this->id = mysql_insert_id();
    }

    function update ($sock) {
      $query = "UPDATE filters
                SET location_id = $this->location_id,
                    filter = '" . addslashes($this->filter) . "'
                WHERE id = $this->id";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }
    }
  }

  class Host {
    var $id;
    var $username;
    var $password;
    var $fullname;
    var $email;
    var $opened;
    var $closed;
    var $active;

    function Host ($sql_result_row, $id, $sock) {
      // If a second argument is passed, then we know we're trying to
      // populate this object by getting the data from the database,
      // based on the id.  We'll just put the data into the
      // sql_result_row variable, so that the next paragraph picks it up.
      if ($id) {
        $query = "SELECT * FROM hosts
                  WHERE id = " . $id;

        if (!$sql_result = mysql_query($query, $sock)) {
          echo mysql_error();
          html_exit();
        }

        if (mysql_num_rows($sql_result) == 1) {
          $sql_result_row = mysql_fetch_row($sql_result);
        }
      }

      // Either 1) the sql_result_row was passed to us as a parameter,
      // or 2) the variable was set in the above paragraph. Either way,
      // populate this object's variables.
      if ($sql_result_row) {
        $this->id = $sql_result_row[0];
        $this->username = stripslashes($sql_result_row[1]);
        $this->password = stripslashes($sql_result_row[2]);
        $this->fullname = stripslashes($sql_result_row[3]);
        $this->email = stripslashes($sql_result_row[4]);
        $this->opened = $sql_result_row[5];
        $this->closed = $sql_result_row[6];
        $this->active = $sql_result_row[7];
      }
      // No parameters, so just return, creating an empty object.
      else
        return;
    }

    function insert ($sock) {
      $query = "INSERT INTO hosts
                VALUES (NULL, '" . addslashes($this->username) . "',
                        '" . addslashes($this->password) . "',
                        '" . addslashes($this->fullname) . "',
                        '" . addslashes($this->email) . "',
                        $this->opened, $this->closed, $this->active)";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }

      $this->id = mysql_insert_id();
    }

    function update ($sock) {
      $query = "UPDATE hosts
                SET username = '" . addslashes($this->username) . "',
                    password = '" . addslashes($this->password) . "',
                    fullname = '" . addslashes($this->fullname) . "',
                    email = '" . addslashes($this->email) . "',
                    opened = $this->opened, closed = $this->closed, 
                    active = $this->active
                WHERE id = $this->id";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }
    }
  }

  class Advertiser {
    var $id;
    var $username;
    var $password;
    var $fullname;
    var $email;
    var $opened;
    var $closed;
    var $active;

    function Advertiser ($sql_result_row, $id, $sock) {
      // If a second argument is passed, then we know we're trying to
      // populate this object by getting the data from the database,
      // based on the id.  We'll just put the data into the
      // sql_result_row variable, so that the next paragraph picks it up.
      if ($id) {
        $query = "SELECT * FROM advertisers
                  WHERE id = " . $id;

        if (!$sql_result = mysql_query($query, $sock)) {
          echo mysql_error();
          html_exit();
        }

        if (mysql_num_rows($sql_result) == 1) {
          $sql_result_row = mysql_fetch_row($sql_result);
        }
      }

      // Either 1) the sql_result_row was passed to us as a parameter,
      // or 2) the variable was set in the above paragraph. Either way,
      // populate this object's variables.
      if ($sql_result_row) {
        $this->id = $sql_result_row[0];
        $this->username = stripslashes($sql_result_row[1]);
        $this->password = stripslashes($sql_result_row[2]);
        $this->fullname = stripslashes($sql_result_row[3]);
        $this->email = stripslashes($sql_result_row[4]);
        $this->opened = $sql_result_row[5];
        $this->closed = $sql_result_row[6];
        $this->active = $sql_result_row[7];
      }
      // No parameters, so just return, creating an empty object.
      else
        return;
    }

    function insert ($sock) {
      $query = "INSERT INTO advertisers
                VALUES (NULL, '" . addslashes($this->username) . "',
                        '" . addslashes($this->password) . "',
                        '" . addslashes($this->fullname) . "',
                        '" . addslashes($this->email) . "',
                        $this->opened, $this->closed, $this->active)";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }

      $this->id = mysql_insert_id();
    }

    function update ($sock) {
      $query = "UPDATE advertisers
                SET username = '" . addslashes($this->username) . "',
                    password = '" . addslashes($this->password) . "',
                    fullname = '" . addslashes($this->fullname) . "',
                    email = '" . addslashes($this->email) . "',
                    opened = $this->opened, closed = $this->closed, 
                    active = $this->active
                WHERE id = $this->id";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }
    }
  }

  class Click {
    var $id;
    var $ad_id;
    var $imp;
    var $time;
    var $dtime;
    var $host;
    var $url;
    var $agent;

    function Click ($sql_result_row, $id, $sock) {
      // If a second argument is passed, then we know we're trying to
      // populate this object by getting the data from the database,
      // based on the id.  We'll just put the data into the
      // sql_result_row variable, so that the next paragraph picks it up.
      if ($id) {
        $query = "SELECT * FROM clicks
                  WHERE id = " . $id;

        if (!$sql_result = mysql_query($query, $sock)) {
          echo mysql_error();
          html_exit();
        }

        if (mysql_num_rows($sql_result) == 1) {
          $sql_result_row = mysql_fetch_row($sql_result);
        }
      }

      // Either 1) the sql_result_row was passed to us as a parameter,
      // or 2) the variable was set in the above paragraph. Either way,
      // populate this object's variables.
      if ($sql_result_row) {
        $this->id = $sql_result_row[0];
        $this->ad_id = $sql_result_row[1];
        $this->imp = $sql_result_row[2];
        $this->time = $sql_result_row[3];
        $this->dtime = $sql_result_row[4];
        $this->host = stripslashes($sql_result_row[5]);
        $this->url = stripslashes($sql_result_row[6]);
        $this->agent = stripslashes($sql_result_row[7]);
      }
      // No parameters, so just return, creating an empty object.
      else
        return;
    }

    function insert ($sock) {
      $query = "INSERT INTO clicks
                VALUES (NULL, $this->ad_id, $this->imp,
                        $this->time, $this->dtime,
                        '" . addslashes($this->host) . "',
                        '" . addslashes($this->url) . "',
                        '" . addslashes($this->agent) . "')";

      if (!$sql_result = mysql_query($query, $sock)) {
        echo mysql_error();
        html_exit();
      }

      $this->id = mysql_insert_id();
    }
  }
?>
