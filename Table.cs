public class Column(string header, List<string> values)
{
    public string Header { get; set; } = header;
    public List<string> Values { get; set; } = values;

    public int GetWidth() {
        return Values.Max(x => x.Length) + 2;
    }
    public int GetHeight() {
        return (Values.Count + 1) * 2 - 1;
    }
}

public class Table
{
    public List<Column> Columns { get; set; } = [];
    private int GetWidth()
    {
        return 1 + Columns.Sum(x => x.GetWidth() + 1);
    }
    private Column GetTallestColumn()
    {
        return Columns.MaxBy(x => x.GetHeight()) ?? Columns.First();
    }
    private string GetLine()
    {
        string line = "+";
        foreach (var col in Columns)
            line += new string('-', col.GetWidth()) + '+';
        return line;
    }
    public void Render()
    {
        int w = GetWidth();
        string line = GetLine();
        Console.WriteLine(line);
        for (int i = 0; i < GetTallestColumn().Values.Count + 1; i++)
        {
            foreach (var col in Columns)
            {
                string val = "";
                if (i == 0)
                {
                    val = col.Header;
                }
                else
                {
                    val = (i - 1) < col.Values.Count ? col.Values[i - 1] : "";
                }
                int padding = col.GetWidth() - val.Length - 2;
                Console.Write($"| {val}{new string(' ', padding)} ");
            }
            Console.Write('|');
            if (i == 0) Console.Write('\n' + line);
            Console.Write('\n');
        }
        Console.WriteLine(line);
    }
    public void Add(string header, List<string> values)
    {
        Columns.Add(new(header, values));
    }
}