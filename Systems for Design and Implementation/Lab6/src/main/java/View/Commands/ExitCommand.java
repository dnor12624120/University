package View.Commands;

public class ExitCommand extends MenuCommand
{
    public ExitCommand(String description, String index)
    {
        super(description, index);
    }

    @Override
    public void execute()
    {
        System.exit(0);
    }
}
