#ifndef aeon_streams_access_mode_mixin_h__
#define aeon_streams_access_mode_mixin_h__

namespace aeon
{
namespace streams
{

/*!
 * The available access modes for the class that uses the access_mode_mixin.
 * This allows an implementation to for it's access permissions.
 *
 * This is implemented as an anonymous enum within a class, since enum classes
 * do not support bit flags at this moment.
 */
class access_mode
{
public:
    enum : int
    {
        none       = 0, /**< No access */
        read       = 1, /**< Read-Only */
        write      = 2, /**< Write-Only */
        read_write = 3  /**< Read-Write (Full access) */
    };
};

class access_mode_mixin
{
public:
    access_mode_mixin() :
        access_mode_(access_mode::none)
    {
    }

    access_mode_mixin(int access) :
        access_mode_(access)
    {
    }

    virtual int get_access_mode() const
    {
        return access_mode_;
    }

    virtual bool is_readable() const
    {
        return (access_mode_ & access_mode::read) != 0;
    }

    virtual bool is_writable() const
    {
        return (access_mode_ & access_mode::write) != 0;
    }

protected:
    void set_access_mode(int access)
    {
        access_mode_ = access;
    }

private:
    /*!
     * Bitflags representing the access mode of this stream.
     * May be read and or write.
     * \sa access_mode
     */
    int access_mode_;
};

} // namespace streams
} // namespace aeon

#endif // aeon_streams_access_mode_mixin_h__

