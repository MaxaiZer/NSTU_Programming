public class StudentService: IStudentService
{
    private List<Student> _list = new();

    public void Add(Student student)
    {
        _list.Add(student);
    }

    public void Clear()
    {
        _list.Clear();
    }

    public IEnumerable<Student> GetAll()
    {
        return _list;
    }
}