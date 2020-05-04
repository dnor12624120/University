package Domain;

public class DatabaseConfig
{
    public String databaseURL;
    public String username;
    public String password;
    public String tableName;

    public DatabaseConfig(String databaseURL, String username, String password, String tableName)
    {
        this.databaseURL = databaseURL;
        this.username = username;
        this.password = password;
        this.tableName = tableName;
    }
}
