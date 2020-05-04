package View.Commands;

public abstract class MenuCommand
{
    private String description;
    private String index;

    public MenuCommand(String description, String index)
    {
        this.description = description;
        this.index = index;
    }

    public abstract void execute();

    public String getDescription() { return description; }
    public String getIndex() { return index; }
}
