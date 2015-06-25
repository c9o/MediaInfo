#include "mediainfo.h"

int
main (int argc, char **argv)
{
  GError *err = NULL;
  GstDiscoverer *dc;
  gint timeout = 10;
  GOptionEntry options[] = {
    {"async", 'a', 0, G_OPTION_ARG_NONE, &async,
        "Run asynchronously", NULL},
    {"timeout", 't', 0, G_OPTION_ARG_INT, &timeout,
        "Specify timeout (in seconds, default 10)", "T"},
    /* {"elem", 'e', 0, G_OPTION_ARG_NONE, &elem_seek, */
    /*     "Seek on elements instead of pads", NULL}, */
    {"toc", 'c', 0, G_OPTION_ARG_NONE, &show_toc,
        "Output TOC (chapters and editions)", NULL},
    {"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose,
        "Verbose properties", NULL},
    {NULL}
  };
  GOptionContext *ctx;

  setlocale (LC_ALL, "");

  ctx =
      g_option_context_new
      ("- discover files synchronously with GstDiscoverer");
  g_option_context_add_main_entries (ctx, options, NULL);
  g_option_context_add_group (ctx, gst_init_get_option_group ());

  if (!g_option_context_parse (ctx, &argc, &argv, &err)) {
    g_print ("Error initializing: %s\n", err->message);
    exit (1);
  }

  g_option_context_free (ctx);

  if (argc < 2) {
    g_print ("usage: %s <uris>\n", argv[0]);
    exit (-1);
  }

  dc = gst_discoverer_new (timeout * GST_SECOND, &err);
  if (G_UNLIKELY (dc == NULL)) {
    g_print ("Error initializing: %s\n", err->message);
    exit (1);
  }

  if (async == FALSE) {
    gint i;
    for (i = 1; i < argc; i++)
      process_file (dc, argv[i]);
  } else {
    PrivStruct *ps = g_new0 (PrivStruct, 1);
    GMainLoop *ml = g_main_loop_new (NULL, FALSE);

    ps->dc = dc;
    ps->argc = argc;
    ps->argv = argv;

    /* adding uris will be started when the mainloop runs */
    g_idle_add ((GSourceFunc) _run_async, ps);

    /* connect signals */
    g_signal_connect (dc, "discovered", G_CALLBACK (_new_discovered_uri), NULL);
    g_signal_connect (dc, "finished", G_CALLBACK (_discoverer_finished), ml);

    gst_discoverer_start (dc);
    /* run mainloop */
    g_main_loop_run (ml);

    gst_discoverer_stop (dc);
    g_free (ps);
    g_main_loop_unref (ml);
  }
  g_object_unref (dc);

  return 0;
}
