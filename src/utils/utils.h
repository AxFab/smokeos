


static inline void emit_try_help (void)
{
  fprintf (stderr, _("Try '%s --help' for more information.\n"), program_name);
}




static inline void init_utilities()
{
  initialize_main (&argc, &argv);
  set_program_name (argv[0]);
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  atexit (close_stdout);
}
