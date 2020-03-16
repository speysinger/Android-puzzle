package net.exit0.androidshare;

import android.content.Intent;
import android.content.Context;
import android.content.ActivityNotFoundException;
import android.text.Html;
import android.net.Uri;
import org.qtproject.qt5.android.bindings.QtActivity;
import android.util.Log;

public class ShareIntent {
  static public void shareText(String title, String subject,
                               String content, QtActivity activity) {
      Intent share = new Intent(Intent.ACTION_SEND);
      share.setType("text/plain");

      share.putExtra(Intent.EXTRA_SUBJECT, subject);
      share.putExtra(Intent.EXTRA_TEXT, Html.fromHtml(content).toString());
      share.putExtra(Intent.EXTRA_HTML_TEXT, content);
      activity.startActivity(Intent.createChooser(share, title));
  }
  static public void shareImage(String title, String subject,
                                String imageURL, QtActivity activity) {
    Intent share = new Intent(Intent.ACTION_SEND);
    Uri imageUri = Uri.parse(imageURL); //This has to be a valid path to image stored in app cache
    share.setType("image/png");         //To share an image

    share.putExtra(Intent.EXTRA_SUBJECT, subject);
    share.putExtra(Intent.EXTRA_STREAM, imageUri);
    activity.startActivity(Intent.createChooser(share, title));
  }
}